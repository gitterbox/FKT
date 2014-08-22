#
#  QCustomPlot Plot Examples
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plot-examples
TEMPLATE = app

SOURCES += main.cpp\
           mainwindow.cpp \
         ../../qcustomplot.cpp \
    db.cpp

HEADERS  += mainwindow.h \
         ../../qcustomplot.h \
    ../db.h \
    db.h

FORMS    += mainwindow.ui

CONFIG += c++11
