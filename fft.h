
#if !defined FFT_H
#define FFT_H

#include <fftw3.h>
#include "SampleComplex.h"
#include <complex>

class FFT
{
public:
    //-----------------------
    // ����������� �������������� �����:
    enum EDirection
    {
        eDirect,   // ������ 
        eReverse   // �������� 
    };
    // ����������� �������������� �����:
    enum EDimentions
    {
        e1D,      // ���������� 
        e2D       // ��������� 
    };
    //-----------------------

private:
    // ���� ���������� �������������� �����
    fftw_plan m_plan;	
    // ����������� (������ | ��������)
    EDirection m_direction;	 
    // ����������� (���������� | ���������)
    EDimentions m_dimension; 
    // ������ ������� �� X, Y
    int m_size_x, m_size_y;
    // ����� ������� �� X, Y
    double m_ms_x, m_ns_y;	
    // ����� ������� �� X, Y
    double m_ks_x, m_ls_y;	

public:
    //����������� 
    // size_x, size_y - ������� �������, �� ��������� size_y=1 (���������� �������)
    // direction - ����������� (������ | ��������), �� ��������� ������
    // dimension - ����������� (���������� | ���������), �� ��������� ����������
    // ms_x, ns_y - ����� ������� �� X, Y
    // ks_x, ls_y - ����� ������� �� X, Y
    FFT(int size_x, int size_y=1, EDirection direction=eDirect, EDimentions dimension=e1D,
        double ms_x=0., double ns_y=0., double ks_x=0., double ls_y=0.);
    //����������
    ~FFT();

    // ������� ������� ���������� �������������� ����� 
    //		(����� ������� � ������� � ���� ����-�� 1/sqrt(n*m) )
    // sample - �������� ������� � ��������� �������������� 
    void Run(SampleComplex& sample);

private:
    // ����� ������� ��� �������
    // sample - ������� 
    // sx, sy - �������� ������ �� x,y 
    void ShiftSample(SampleComplex& sample, double sx, double sy);
};
/////////////////////////////////////////////////////////////////////////////
#endif //defined FFT_H