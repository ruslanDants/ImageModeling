#include "fft.h"
#include <cmath>

FFT::FFT(int size_x, int size_y, EDirection direction, EDimentions dimension,
        double ms_x, double ns_y, double ks_x, double ls_y)
{
	m_direction = direction;	 
    m_dimension = dimension; 
    m_size_x = size_x;
	m_size_y = size_y;
    m_ms_x = ms_x;
	m_ns_y = ns_y;
	m_ks_x = ks_x;
	m_ls_y = ls_y;
}

FFT::~FFT(void)
{
}

void FFT::Run(SampleComplex& sample)
{
	ShiftSample(sample, m_ks_x, m_ls_y);
	if (m_dimension == FFT::e2D)
		m_plan = fftw_plan_dft_2d(m_size_x, m_size_y, (fftw_complex*) sample.GetPointer(), 
												  (fftw_complex*) sample.GetPointer(), 
												   m_direction, FFTW_ESTIMATE);
	else 
		m_plan = fftw_plan_dft_1d(m_size_x, (fftw_complex*) sample.GetPointer(), 
												  (fftw_complex*) sample.GetPointer(), 
												   m_direction, FFTW_ESTIMATE);
	fftw_execute(m_plan);
	double size = m_size_x * m_size_y;
	std::complex<double> k((1 / sqrt(size)), 0);
	sample *= k;
	ShiftSample(sample, m_ms_x, m_ns_y);
	fftw_destroy_plan(m_plan);
}

void FFT::ShiftSample(SampleComplex& sample, double sx, double sy)
{
	double ks, ls, k;
	for (int x = 0; x < m_size_x; x++)
		for (int y = 0; y < m_size_y; y++)
		{
			k =((-2)*PI*sx*x/m_size_x) + ((-2)*PI*sx*y/m_size_y);
            std::complex<double> kk(cos(k), sin(k));
            sample(x, y) *= kk;
		}
}
