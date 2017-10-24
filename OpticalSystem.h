#if !defined  OPTICAL_SYSTEM_H
#define OPTICAL_SYSTEM_H

#include "SampleComplex.h"
#include "object.h"
#include <fftw3.h>
#include "fft.h"
#include <fstream>
#include <qvector.h>
#include "qcustomplot.h"

//-------------------------------------------------------------------------------------------------
class OpticalSystem
{
private:
	// ���������� ���������
	// ����� �����
	double m_lambda;
	// ��������
	double m_aperture;
	// �������������� ���������
	// ����� ������ (������ ���� ������� � �.�.)
	double m_pupil_coverage;
	// ��� �� ������ � �.�.
	double m_dro;
	// ��� �� �������� � �.�.
	double m_dx;
	// ����������� �������� ���������
	double m_c22;
	// ����������� ��������������
	double m_c20;
public:
	// �����������
	// lambda - ����� �����
	// aperture - ��������
	// d_ro - ��� �� ������ � �.�.
	// pupil_coverage - ����� ������ (������ ���� ������� � �.�.)
	OpticalSystem(double lambda, double aperture, double dro, double dx, double c22, double c20, double pupil_coverage = 4.);
	//����������
	~OpticalSystem();

	// ���������� ������������ �����������
	// object - �������
	// image - �����������
	void CalcCoherent(const Object& object, SampleComplex& image);
	// ���������� �������������� �����������
	// object - �������
	// image - �����������
	void CalcNonCoherent(const Object& ob, SampleComplex& image, SampleComplex& psf, SampleComplex& otf);
	// ���������� ��������-������������ �����������
	// object - �������
	// image - �����������
    void CalcPartCoherent(const Object& object, SampleComplex& image, double RadiusSource);
	void Pupil(SampleComplex& field);
private:
	// ��������������� ���� ����� ���������� �������(������)
	// field - ����, ���������� ����� ������
	
};
//-------------------------------------------------------------------------------------------------
#endif
