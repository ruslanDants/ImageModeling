
#if !defined FFT_H
#define FFT_H

#include <fftw3.h>
#include "SampleComplex.h"
#include <complex>

class FFT
{
public:
    //-----------------------
    // направление преобразования Фурье:
    enum EDirection
    {
        eDirect,   // прямое 
        eReverse   // обратное 
    };
    // размерность преобразования Фурье:
    enum EDimentions
    {
        e1D,      // одномерное 
        e2D       // двумерное 
    };
    //-----------------------

private:
    // план вычислений преобразования Фурье
    fftw_plan m_plan;	
    // направление (прямое | обратное)
    EDirection m_direction;	 
    // размерность (одномерное | двумерное)
    EDimentions m_dimension; 
    // размер выборки по X, Y
    int m_size_x, m_size_y;
    // сдвиг спектра по X, Y
    double m_ms_x, m_ns_y;	
    // сдвиг выборки по X, Y
    double m_ks_x, m_ls_y;	

public:
    //конструктор 
    // size_x, size_y - размеры выборки, по умолчанию size_y=1 (одномерная выборка)
    // direction - направление (прямое | обратное), по умолчанию прямое
    // dimension - размерность (одномерное | двумерное), по умолчанию одномерное
    // ms_x, ns_y - сдвиг спектра по X, Y
    // ks_x, ls_y - сдвиг выборки по X, Y
    FFT(int size_x, int size_y=1, EDirection direction=eDirect, EDimentions dimension=e1D,
        double ms_x=0., double ns_y=0., double ks_x=0., double ls_y=0.);
    //деструктор
    ~FFT();

    // функция полного сдвигового преобразования Фурье 
    //		(сдвиг выборки и спектра и учет коэф-та 1/sqrt(n*m) )
    // sample - исходная выборка и результат преобразования 
    void Run(SampleComplex& sample);

private:
    // сдвиг выборки или спектра
    // sample - выборка 
    // sx, sy - величина сдвига по x,y 
    void ShiftSample(SampleComplex& sample, double sx, double sy);
};
/////////////////////////////////////////////////////////////////////////////
#endif //defined FFT_H