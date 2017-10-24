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
	// ������ �����������
	// size - ���������� ���������, ���������� �� x � y (size*size)
	SampleComplex(int size);
	// ����������
	virtual ~SampleComplex();

	// ���������� ������������� ������� (������� ������) 
	// ������������ � ������������ �����, ������ ����� ����������
	void CalcIntens();

	// ����� � ���� ������ ������������ ����� �������
	ostream& PrintReal(ostream& out);
	// ����� � ���� ������ ������ ����� �������
	ostream& PrintImag(ostream& out);

	// ����� � ���� ������ �������
	ostream& PrintModule(ostream& out);
	// ����� � ���� ���� �������
	ostream& PrintPhase(ostream& out);
	// ����� � ���� ������������� ������� (������� ������)
	ostream& PrintIntens(ostream& out);
};
//-------------------------------------------------------------------------------------------------
#endif