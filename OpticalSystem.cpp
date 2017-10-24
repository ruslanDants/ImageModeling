#include "OpticalSystem.h"


OpticalSystem::OpticalSystem(double lambda, double aperture, double dro, double dx,  double c22, double c20, double pupil_coverage)
	:m_lambda(lambda), m_aperture(aperture), m_dro(dro), m_dx(dx), m_pupil_coverage(pupil_coverage), m_c22(c22), m_c20(c20)
{
}
void OpticalSystem::CalcCoherent(const Object& object, SampleComplex& image)
{
	SampleComplex Ob(object.GetSize());
	for (int i = 0; i < object.GetSize(); i++)
	{
		for (int k = 0; k < object.GetSize(); k++)
		{
			Ob(i,k) = object(i,k);
		}
	}
	FFT Fourier2D(object.GetSize(), object.GetSize(), 
		FFT::eDirect, FFT::e2D, object.GetSize()/2, object.GetSize()/2, object.GetSize()/2, object.GetSize()/2);
	Fourier2D.Run(Ob);
	SampleComplex pupil(object.GetSize());
	Pupil(pupil);
	image = Ob;
	image *= pupil;
	FFT Fourier2DReverse(object.GetSize(), object.GetSize(), 
		FFT::eReverse, FFT::e2D, object.GetSize()/2, object.GetSize()/2, object.GetSize()/2, object.GetSize()/2);
	Fourier2DReverse.Run(image);
}

void OpticalSystem::CalcNonCoherent(const Object& object, SampleComplex& image, SampleComplex& psf, SampleComplex& otf)
{
	// ���������� �����-������ ������������� ������������� �� ��������:
	SampleComplex Ob(object.GetSize());
	for (int i = 0; i < object.GetSize(); i++)
		for (int k = 0; k < object.GetSize(); k++)
			Ob(i,k) = object(i,k);
	Ob.CalcIntens();
	FFT Fourier2D(object.GetSize(), object.GetSize(), 
		FFT::eDirect, FFT::e2D, object.GetSize()/2, object.GetSize()/2, object.GetSize()/2, object.GetSize()/2);
	Fourier2D.Run(Ob);
	// ���������� �����-������ ������� ��������� �����
	SampleComplex pupil(object.GetSize());
	Pupil(pupil);
	FFT Fourier2DReverse(pupil.GetSize(), pupil.GetSize(), 
		FFT::eReverse, FFT::e2D, pupil.GetSize()/2, pupil.GetSize()/2, pupil.GetSize()/2, pupil.GetSize()/2);
	Fourier2DReverse.Run(pupil);
	pupil.CalcIntens();
	double max = 0;
    for (int i = 0; i < pupil.GetSize(); i++)
        for (int k = 0; k < pupil.GetSize(); k++)
            if (max < pupil(i, k).real())
                max = pupil(i, k).real();
	pupil /= max;
	psf = pupil;
	Fourier2D.Run(pupil);
	max = 0;
	for (int i = 0; i < pupil.GetSize(); i++)
        for (int k = 0; k < pupil.GetSize(); k++)
            if (max < pupil(i, k).real())
                max = pupil(i, k).real();
	pupil /= max;
	otf = pupil;
	// ���������� �����-������ ������������� ������������� �� �����������
	image = Ob;
	image *= pupil;
	// ���������� ������������� ������������� �� �����������
	FFT Four2DReverse(pupil.GetSize(), pupil.GetSize(), 
		FFT::eReverse, FFT::e2D, pupil.GetSize()/2, pupil.GetSize()/2, pupil.GetSize()/2, pupil.GetSize()/2);
	Four2DReverse.Run(image);
}

void OpticalSystem::CalcPartCoherent(const Object& object, SampleComplex& image, double RadiusSource)
{
	//����������� �������� � ��������� ������
	SampleComplex Ob(object.GetSize());
	for (int i = 0; i < object.GetSize(); i++)
		for (int k = 0; k < object.GetSize(); k++)
			Ob(i,k) = object(i,k);
	// ������ �������
	int size = object.GetSize();
	// ��������� ������� �������������� �����
	FFT Fourier2D(size, size, FFT::eDirect, FFT::e2D, size/2, size/2, size/2, size/2);
	// ��������� ��������� �������������� �����
	FFT Fourier2DReverse(size, size, FFT::eReverse, FFT::e2D, size/2, size/2, size/2, size/2);

	// ��������� �������� � �����������
	image.SetValue(std::complex<double> (0, 0));
	// �������� ������
	SampleComplex pupil(size);
	Pupil(pupil); 
	double py_source, px_source; // ������������ ��������� ���������� ��������
	// ������� �����
	SampleComplex U(size);
	int count=0;
	// ���� �� ������ ���������
	for (int i = 0; i < size; i++)
	{
		py_source = pupil.CalcCoord(i, m_dro);
		for (int k = 0; k < size; k++)
		{
			px_source = pupil.CalcCoord(k, m_dro);
			if ((py_source*py_source + px_source*px_source) <= RadiusSource*RadiusSource) // ������� ��� ����� ������ �� ��������� � �������� RadiusSource
			// ���������� ��������-������������� ��������� �� ����� ����� ���������
			{
				count++;
				double py_object, px_object; // ������������ ��������� ���������� ��������
				// ���� �� ������ ��������
				for (int t = 0; t < size; t++)
				{
					py_object = object.CalcCoord(t, m_dx);
					for (int n = 0; n < size; n++)
					{
						px_object = object.CalcCoord(n, m_dx);
						// ���������� ��������� ������� �����
						double k =((-2)*PI*px_source * px_object) + ((-2)*PI*py_source * py_object);
						//std::complex<double> B(cos(k), sin(k));
						// ����������� ���� ����� �������
						//U.SetValue(B);
						U(t, n) = std::complex<double> (cos(k), sin(k));
						//U.SetValue(std::complex<double> (cos(k), sin(k)));
					}
				}
				U *= Ob;
				// �����
				Fourier2D.Run(U);
				// ��������������� ���� ����� ���������� �������
				U *= pupil;
				// ������������� ��������������� ���� � ������������ �����������
				Fourier2DReverse.Run(U);
				// ���������� ������������� ������������� �� �����������, ���������� ��� ��������� ��������� ������ ���������
				U.CalcIntens();
				image += U;
			}
		}
		
	}
	image /= count;
}


void OpticalSystem::Pupil(SampleComplex& field)
{
	double py_in, px_in; // ������������ ��������� ����������
	double radius_2 = 0;
	for (int i = 0; i < field.GetSize(); i++)
	{
		py_in = field.CalcCoord(i, m_dro);
		for (int k = 0; k < field.GetSize(); k++)
		{
			px_in = field.CalcCoord(k, m_dro);
			radius_2 = py_in*py_in + px_in*px_in;
			if ((radius_2) <= 1) // ��������� ������� 
			{
				if (!m_c22)
				{
					field.operator()(i, k) = 1;
				}
				else
				{
					double phi = 2 * px_in * px_in / radius_2 - 1;
					double W20=m_c20*((2*radius_2)-1);
					double W22=m_c22*radius_2*(phi);
					double t =(-2)*PI*(W20 + W22);
					field.operator()(i, k) = std::complex<double> (cos(t), sin(t));
				}
			}
				
			else 
				field.operator()(i, k) = 0;
		}
	}
}
OpticalSystem::~OpticalSystem()
{
}
