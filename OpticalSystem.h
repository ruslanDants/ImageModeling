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
	// оптические параметры
	// длина волны
	double m_lambda;
	// апертура
	double m_aperture;
	// вычислительные параметры
	// охват зрачка (размер всей выборки в к.е.)
	double m_pupil_coverage;
	// шаг по зрачку в к.е.
	double m_dro;
	// шаг по предмету в к.е.
	double m_dx;
	// коэффициент волновой аберрации
	double m_c22;
	// коэффициент расфокусировки
	double m_c20;
public:
	// конструктор
	// lambda - длина волны
	// aperture - апертура
	// d_ro - шаг по зрачку в к.е.
	// pupil_coverage - охват зрачка (размер всей выборки в к.е.)
	OpticalSystem(double lambda, double aperture, double dro, double dx, double c22, double c20, double pupil_coverage = 4.);
	//деструктор
	~OpticalSystem();

	// вычисление когерентного изображения
	// object - предмет
	// image - изображение
	void CalcCoherent(const Object& object, SampleComplex& image);
	// вычисление некогерентного изображения
	// object - предмет
	// image - изображение
	void CalcNonCoherent(const Object& ob, SampleComplex& image, SampleComplex& psf, SampleComplex& otf);
	// вычисление частично-когерентного изображения
	// object - предмет
	// image - изображение
    void CalcPartCoherent(const Object& object, SampleComplex& image, double RadiusSource);
	void Pupil(SampleComplex& field);
private:
	// распространение поля через оптическую систему(зрачок)
	// field - поле, проходящее через зрачок
	
};
//-------------------------------------------------------------------------------------------------
#endif
