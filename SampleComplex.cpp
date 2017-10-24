
#include "SampleComplex.h"
//-------------------------------------------------------------------------------------------------
// ������ �����������
SampleComplex::SampleComplex(int size)
	: Sample<complex<double> >(size)
{
}
//-------------------------------------------------------------------------------------------------
// ����������
SampleComplex::~SampleComplex()
{

}
//-------------------------------------------------------------------------------------------------
// ���������� ������������� ������� (������� ������) 
// ������������ � ������������ �����, ������ ����� ����������
void SampleComplex::CalcIntens()
{
	for (int i = 0; i<m_size; ++i)
	{
		for (int j = 0; j<m_size; ++j)
		{
			double res = operator()(i, j).real()*operator()(i, j).real() +
				operator()(i, j).imag()*operator()(i, j).imag();
			operator()(i, j) = complex<double>(res, 0.);
		}
	}
}
//-------------------------------------------------------------------------------------------------
// ����� � ���� ������ ������������ ����� �������
ostream& SampleComplex::PrintReal(ostream& out)
{
	for (int i = 0; i<m_size; i++)
	{
		for (int j = 0; j<m_size; j++)
		{
			out << operator()(i, j).real() << " ";
		}
		out << endl;
	}
	return out;
}
//-------------------------------------------------------------------------------------------------
// ����� � ���� ������ ������ ����� �������
ostream& SampleComplex::PrintImag(ostream& out)
{
	for (int i = 0; i<m_size; i++)
	{
		for (int j = 0; j<m_size; j++)
		{
			out << operator()(i, j).imag() << " ";
		}
		out << endl;
	}
	return out;
}
//-------------------------------------------------------------------------------------------------
// ����� � ���� ������ �������
ostream& SampleComplex::PrintModule(ostream& out)
{
	complex<double> x;
	for (int i = 0; i<m_size; i++)
	{
		for (int j = 0; j<m_size; j++)
		{
			double res = sqrt(operator()(i, j).real()*operator()(i, j).real() +
				operator()(i, j).imag()*operator()(i, j).imag());
			out << res << " ";
		}
		out << endl;
	}
	return out;
}
//-------------------------------------------------------------------------------------------------
// ����� � ���� ������ �������
ostream& SampleComplex::PrintPhase(ostream& out)
{
	complex<double> x;
	for (int i = 0; i<m_size; i++)
	{
		for (int j = 0; j<m_size; j++)
		{
			double res = atan2(operator()(i, j).imag(), operator()(i, j).real());
			out << res << " ";
		}
		out << endl;
	}
	return out;
}
//-------------------------------------------------------------------------------------------------
// ����� � ���� ������������� ������� (������� ������)
ostream& SampleComplex::PrintIntens(ostream& out)
{
	for (int i = 0; i<m_size; i++)
	{
		for (int j = 0; j<m_size; j++)
		{
			double res = operator()(i, j).real()*operator()(i, j).real() +
				operator()(i, j).imag()*operator()(i, j).imag();
			out << res << " ";
		}
		out << endl;
	}
	return out;
}
//-------------------------------------------------------------------------------------------------