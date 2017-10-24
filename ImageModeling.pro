#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T04:06:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ImageModeling
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Object.cpp \
    OpticalSystem.cpp \
    qcustomplot.cpp \
    SampleComplex.cpp \
    fft.cpp

HEADERS  += mainwindow.h \
    Object.h \
    OpticalSystem.h \
    qcustomplot.h \
    Sample.h \
    SampleComplex.h \
    fft.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/fftw/
LIBS +=  $$PWD/fftw/libfftw3-3.a\
         $$PWD/fftw/libfftw3f-3.a\
         $$PWD/fftw/libfftw3l-3.a
