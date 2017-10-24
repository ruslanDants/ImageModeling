#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), obj(512, 0.01), img(512), psf(512), otf(512)
{
	ui.setupUi(this);	
	Ap = 10;
	lambda = 0.45;
	deltaN = 0;
	deltaP = 0;
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(Calc()));
	connect(ui.action_exit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.action_exportObj, SIGNAL(triggered()), this, SLOT(exportObject()));
}
void MainWindow::Calc()
{
	period = ui.tableWidget->item(0,0)->text().toDouble();
	width = ui.tableWidget->item(1,0)->text().toDouble();
	size = ui.tableWidget->item(2,0)->text().toInt();
	pupil = ui.tableWidget->item(3,0)->text().toDouble();
	double koef_Coherent = ui.tableWidget->item(4,0)->text().toDouble();
	c22 = ui.tableWidget->item(5,0)->text().toDouble();
	c20 = ui.tableWidget->item(6,0)->text().toDouble();
	if (ui.radioButton->isChecked()) typeIllumination = 0;
	if (ui.radioButton_2->isChecked()) typeIllumination = 1;
	if (ui.radioButton_3->isChecked()) typeIllumination = 2;

	deltaP = pupil / size;
	deltaN = 1 / (size * deltaP);
	
	radius = koef_Coherent; 

	obj = Object(size, deltaN);
	obj.CreateLineAndSpace(period, width);
	img = SampleComplex(size);
	psf = SampleComplex(size);
	otf = SampleComplex(size);
	OpticalSystem System(lambda, Ap, deltaP, deltaN, c22, c20, pupil);
	switch (typeIllumination)
	{
		case 0:
		{
			System.CalcCoherent(obj, img);
			PlotObjImg(obj, img, ui.widget, ui.widget_3, ui.widget_2);
			ui.toolBox->setItemEnabled(1, false);
			ui.toolBox->setItemEnabled(2, false);
			break;
		}
		case 1:
		{
			System.CalcNonCoherent(obj, img, psf, otf);
			PlotObjImg(obj, img, ui.widget, ui.widget_3, ui.widget_2);
			PlotPSF(psf, ui.widget_4, ui.widget_6);
			PlotOTF(otf, ui.widget_5);
			ui.toolBox->setItemEnabled(1, true);
			ui.toolBox->setItemEnabled(2, true);
			break;
		}
		case 2:
		{
			System.CalcPartCoherent(obj, img, radius);
			PlotObjImg(obj, img, ui.widget, ui.widget_3, ui.widget_2);
			ui.toolBox->setItemEnabled(1, false);
			ui.toolBox->setItemEnabled(2, false);

		}

	}

	/*if (typeIllumination)
	{
		System.CalcCoherent(obj, img);
		PlotObjImg(obj, img, ui.widget, ui.widget_3, ui.widget_2);
		ui.toolBox->setItemEnabled(1, false);
		ui.toolBox->setItemEnabled(2, false);
	}
	else
	{
		System.CalcNonCoherent(obj, img, psf, otf);
		PlotObjImg(obj, img, ui.widget, ui.widget_3, ui.widget_2);
		PlotPSF(psf, ui.widget_4, ui.widget_6);
		PlotOTF(otf, ui.widget_5);
		ui.toolBox->setItemEnabled(1, true);
		ui.toolBox->setItemEnabled(2, true);
	
	}*/
}
void MainWindow::PlotObjImg(Object& object, SampleComplex& image, QCustomPlot *ObjImg, QCustomPlot *SpectrObj, QCustomPlot *SpectrImg)
{
	ObjImg->clearGraphs();
	ObjImg->addGraph();
	ObjImg->addGraph();

	ObjImg->graph(0)->setPen(QPen(Qt::black));
	ObjImg->graph(1)->setPen(QPen(Qt::red));
	ObjImg->yAxis->setRange(-0.5, 1.2);

	SpectrObj->clearGraphs();
	QCPColorMap *spectr_obj = new QCPColorMap(SpectrObj->xAxis, SpectrObj->yAxis);
	SpectrObj->addPlottable(spectr_obj);
	SpectrObj->xAxis->setLabel("x");
	SpectrObj->yAxis->setLabel("y");
	spectr_obj->data()->setSize(object.GetSize(), object.GetSize());

	SpectrImg->clearGraphs();
	QCPColorMap *spectr_img = new QCPColorMap(SpectrImg->xAxis, SpectrImg->yAxis);
	SpectrImg->addPlottable(spectr_img);
	SpectrImg->xAxis->setLabel("x");
	SpectrImg->yAxis->setLabel("y");
	spectr_img->data()->setSize(object.GetSize(), object.GetSize());

	double x, y, valueObj, valueImg;
	int dim = object.GetSize() / 2;
	double min = (0.5-dim)*deltaN;
	double max = (0.5+dim)*deltaN;
	ObjImg->xAxis->setRange(min, max);
	spectr_obj->data()->setRange(QCPRange(min, max), QCPRange(min, max));
	spectr_img->data()->setRange(QCPRange(min, max), QCPRange(min, max));
	for (int i = 0; i < object.GetSize(); i++)
	{
		y = (i+0.5-dim)*deltaN;
		for (int k = 0; k < object.GetSize(); k++)
		{
			x = (k+0.5-dim)*deltaN;
			valueObj = object(i, k).real();
			spectr_obj->data()->setCell(i, k, valueObj);
			valueImg = image(i, k).real();
			spectr_img->data()->setCell(i, k, valueImg);
			if (i == dim)
			{
				ObjImg->graph(0)->addData(x, valueObj);
				ObjImg->graph(1)->addData(x, valueImg);
			}
		}
	}
	ObjImg->replot();
	spectr_obj->setGradient(QCPColorGradient::gpGrayscale);
	spectr_obj->rescaleDataRange();
	SpectrObj->rescaleAxes();
	SpectrObj->replot();
	spectr_img->setGradient(QCPColorGradient::gpGrayscale);
	spectr_img->rescaleDataRange();
	SpectrImg->rescaleAxes();
	SpectrImg->replot();
}
void MainWindow::PlotPSF(SampleComplex& psf, QCustomPlot *curve, QCustomPlot *spectr)
{
	curve->clearGraphs();
	curve->addGraph();
	curve->graph(0)->setPen(QPen(Qt::black));
	curve->yAxis->setRange(-0.5, 1.2);

	spectr->clearGraphs();
	QCPColorMap *spectr_map = new QCPColorMap(spectr->xAxis, spectr->yAxis);
	spectr->addPlottable(spectr_map);
	spectr->xAxis->setLabel("x");
	spectr->yAxis->setLabel("y");
	spectr_map->data()->setSize(psf.GetSize(), psf.GetSize());

	double x, y, value;
	int dim = psf.GetSize() / 2;
	double min = (0.5-dim)*deltaN;
	double max = (0.5+dim)*deltaN;
	curve->xAxis->setRange(min, max);
	spectr_map->data()->setRange(QCPRange(min, max), QCPRange(min, max));
	for (int i = 0; i < psf.GetSize(); i++)
	{
		y = (i+0.5-dim)*deltaN;
		for (int k = 0; k < psf.GetSize(); k++)
		{
			x = (k+0.5-dim)*deltaN;
			value = psf(i, k).real();
			spectr_map->data()->setCell(i, k, value);
			if (i == dim)
			{
				curve->graph(0)->addData(x, value);
			}
		}
	}
	curve->replot();
	spectr_map->setGradient(QCPColorGradient::gpGrayscale);
	spectr_map->rescaleDataRange();
	spectr->rescaleAxes();
	spectr->replot();
}

void MainWindow::PlotOTF(SampleComplex& otf, QCustomPlot *curve)
{
	curve->clearGraphs();
	curve->addGraph();
	curve->graph(0)->setPen(QPen(Qt::black));
	curve->yAxis->setRange(-0.5, 1.2);

	double x, y, value;
	int dim = otf.GetSize() / 2;
	double min = (0.5-dim)*deltaN;
	double max = (0.5+dim)*deltaN;
	curve->xAxis->setRange(0, 2.5);
	for (int k = 0; k < otf.GetSize(); k++)
	{
		x = (k+0.5-dim)*deltaP;
		value = otf(dim, k).real();
		curve->graph(0)->addData(x, value);
	}
	curve->replot();
}

MainWindow::~MainWindow()
{

}
