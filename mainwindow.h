#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "OpticalSystem.h"
#include "qcustomplot.h"
#include <qfiledialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void Calc();
private:
	Ui::MainWindow ui;
	double period;
	double width;
	double pupil;
	double radius;
	int size;
	int typeIllumination;
	double Ap;
	double lambda;
	double deltaP;
	double deltaN;
	double c22;
	double c20;
	Object obj;
	SampleComplex img;
	SampleComplex psf;
	SampleComplex otf;
	void PlotObjImg(Object& object, SampleComplex& image, 
		QCustomPlot *ObjImg, QCustomPlot *SpectrObj, QCustomPlot *SpectrImg);
	void PlotPSF(SampleComplex& psf, QCustomPlot *curve, QCustomPlot *spectr);
	void PlotOTF(SampleComplex& otf, QCustomPlot *curve);
};

#endif // MAINWINDOW_H
