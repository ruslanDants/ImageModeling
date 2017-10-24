#if !defined  SAMPLE_COMPLEX_H
#define SAMPLE_COMPLEX_H

#include "Sample.h"
#include <complex>
using namespace std;

#define PI 3.14159265358979
//-------------------------------------------------------------------------------------------------
class SampleComplex : public Sample<complex<double> >
{
public:
	// полный конструктор
	// size - количество элементов, одинаковое по x и y (size*size)
	SampleComplex(int size);
	// деструктор
	virtual ~SampleComplex();

	// вычисление интенсивности выборки (квадрат модуля) 
	// записывается в вещественную часть, мнимая часть обнуляется
	void CalcIntens();

	// вывод в файл только вещественной части выборки
	ostream& PrintReal(ostream& out);
	// вывод в файл только мнимой части выборки
	ostream& PrintImag(ostream& out);

	// вывод в файл модуля выборки
	ostream& PrintModule(ostream& out);
	// вывод в файл фазы выборки
	ostream& PrintPhase(ostream& out);
	// вывод в файл интенсивности выборки (квадрат модуля)
	ostream& PrintIntens(ostream& out);
};
//-------------------------------------------------------------------------------------------------
#endif