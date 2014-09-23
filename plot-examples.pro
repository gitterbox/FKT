#
#  QCustomPlot Plot Examples
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = plot-examples
TEMPLATE = app

SOURCES += main.cpp\
           mainwindow.cpp \
    db.cpp \
    gui.cpp \
    ../qcp/qcustomplot.cpp

HEADERS  += mainwindow.h \
    db.h \
    gui.h \
    ../qcp/qcustomplot.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    renku.qrc
