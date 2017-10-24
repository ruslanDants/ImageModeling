
#include "SampleComplex.h"
//-------------------------------------------------------------------------------------------------
// полный конструктор
SampleComplex::SampleComplex(int size)
	: Sample<complex<double> >(size)
{
}
//-------------------------------------------------------------------------------------------------
// деструктор
SampleComplex::~SampleComplex()
{

}
//-------------------------------------------------------------------------------------------------
// вычисление интенсивности выборки (квадрат модуля) 
// записывается в вещественную часть, мнимая часть обнуляется
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
// вывод в файл только вещественной части выборки
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
// вывод в файл только мнимой части выборки
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
// вывод в файл модуля выборки
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
// вывод в файл модуля выборки
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
// вывод в файл интенсивности выборки (квадрат модуля)
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