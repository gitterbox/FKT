/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013 Emanuel Eichhammer                     **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 09.12.13                                             **
**          Version: 1.1.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#include "mainwindow.h"
//header file of mainwindow
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

#include "db.h"
#include <iostream>

#include <unistd.h>

using namespace std;

 void MainWindow::openFile(){
     QString fileName = QFileDialog::getOpenFileName(this);
     //set to class member filename
     filename = fileName;

     QFile file(fileName);
     if (file.open(QIODevice::ReadOnly|QIODevice::Text)){

         //http://stackoverflow.com/questions/11191762/qt-qstring-to-stdstring
         std::string utf8_text = fileName.toUtf8().constData();
         // or this if you on Windows :-)
         //std::string current_locale_text = qs.toLocal8Bit().constData();
         db.read(utf8_text);
         cout << utf8_text << endl;
         QString head("Datei ");
         QString foot(" erfolgreich geladen");
         statusBar()->showMessage(head+fileName+foot);
     }

 }

 void::MainWindow::createGif(){
    //ui->customPlot->
    // for making screenshots of the current demo or all demos (for website screenshots):
    QTimer::singleShot(2500, this, SLOT(allScreenShots()));
    //QTimer::singleShot(1000, this, SLOT(screenShot()));
    QString head(" ... erstelle GIF ...  ");
    statusBar()->showMessage(filename+head);
 }

 MainWindow::MainWindow(QWidget * parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    //calls setupUi method of mainwindow
	ui->setupUi(this);
    //sets some geometry
	setGeometry(400, 250, 842, 390);
    //sets ui action for openFile
    connect( ui->actionOeffnen, SIGNAL(triggered(bool)), this, SLOT(openFile()));
    //sets ui cation for createGif
    connect( ui->actionGif_Datei_erstellen, SIGNAL(triggered(bool)), this, SLOT(createGif()));

    //######################################################
    cout << "4 dbread" << endl;
    //db.read
	    ("/home/rene/Documents/Projekte/informatik/stick/GLP/Einlesen.csv");
	currentRow = 2;
	cnt = 0;
    maxpics = 30;
    delay = 350;
    //######################################################
    //setupDemo(16);
	//QTimer::singleShot(500, this, SLOT(screenShot()));

   setupPlayground(ui->customPlot);
}

void MainWindow::setupDemo(int demoIndex)
{
	switch (demoIndex) {
	case 18:
		//values = db.getLine(8);
		setupGLPDemo(ui->customPlot);
		break;
	case 19:
		//values = db.getLine(9);
		setupGLPDemo(ui->customPlot);
		break;
	case 20:
		//values = db.getLine(10);
		setupGLPDemo(ui->customPlot);
		break;
	case 21:
		//values = db.getLine(11);
		setupGLPDemo(ui->customPlot);
		break;
	case 22:
		//values = db.getLine(11);
		setupGLPDemo(ui->customPlot);
		break;
	}
	setWindowTitle("QCustomPlot: " + demoName);
	statusBar()->clearMessage();
	currentDemoIndex = demoIndex;
	ui->customPlot->replot();
}


//not used yet
void MainWindow::plotData(int row)
{
	QCustomPlot *customPlot = ui->customPlot;

	QString s = QString::number(row - 2);
	demoName = "GLP_row:" + s + "°";

	//amount of values of row
	int max = 30;
	//double step = 1/max;
	Database db;
	db.read("/media/exchange/PortableApps/Documents/GLP/Einlesen.csv");
	double *values;
	values = db.getLine(row);

	QVector < double >x(max), y(max);	// initialize with entries 0..100
	for (int i = 1; i < max; ++i) {
		if (values[i] > -1 && values[i] < 1) {
			x[i] = values[i];	// x goes from -1 to 1
			cout << i << " x:" << x[i];
		}
		y[i] = 1 - (i * 0.03);
		cout << i << " y:" << y[i] << endl;
	}
	// create graph and assign data to it:

	int i = 2;
	QPen pen;
	customPlot->addGraph();
	pen.setColor(QColor
		     (sin(i * 1 + 1.2) * 80 + 80, sin(i * 0.3 + 0) * 80 + 80,
		      sin(i * 0.3 + 1.5) * 80 + 80));
	customPlot->graph()->setLineStyle(QCPGraph::lsNone);
	customPlot->
	    graph()->setScatterStyle(QCPScatterStyle
				     (QCPScatterStyle::ssCircle, 9));

	customPlot->graph()->setData(x, y);
	// give the axes some labels:
	QString valueAsString = QString::number(values[0]);
	const QString xax = "x " + valueAsString + " Grad";
	//string xlabel = "x "<<values[0]<<" Grad"
	customPlot->xAxis->setLabel(xax);
	customPlot->yAxis->setLabel("y");
	// set axes ranges, so we see all data:
	customPlot->xAxis->setRange(-1, 1);
	customPlot->yAxis->setRange(1, 0);
	//TODO: Plot to Image Export ?
	delete[]values;
}

void MainWindow::setupGLPDemo(QCustomPlot * customPlot)
{
    currentRow++;
	double *values;
	//values = db.getLine2();//randomdata
	values = db.getLine(currentRow);
	demoName = "GLP";
	// generate some data:
	int max = 30;
	//double step = 1/max;

	QVector < double >x(max), y(max);	// initialize with entries 0..100
	for (int i = 1; i < max; ++i) {
		if (values[i] > -1 && values[i] < 1) {
			x[i] = values[i];	// x goes from -1 to 1
			cout << i << " x:" << x[i];
		}
		y[i] = 1 - (i * 0.03);
		cout << i << " y:" << y[i] << endl;
	}
	// create graph and assign data to it:
	int i = 2;
	QPen pen;
	customPlot->addGraph();
	pen.setColor(QColor
		     (sin(i * 1 + 1.2) * 80 + 80, sin(i * 0.3 + 0) * 80 + 80,
		      sin(i * 0.3 + 1.5) * 80 + 80));
	customPlot->graph()->setLineStyle(QCPGraph::lsNone);
	customPlot->
	    graph()->setScatterStyle(QCPScatterStyle
				     (QCPScatterStyle::ssCircle, 9));

	customPlot->graph()->setData(x, y);
	// give the axes some labels:
	QString valueAsString = QString::number(values[0]);
	const QString xax = "x-Achse | " + valueAsString + " Grad";
	//string xlabel = "x "<<values[0]<<" Grad"
	customPlot->xAxis->setLabel(xax);
	customPlot->yAxis->setLabel("y-Achse");
	// set axes ranges, so we see all data:
	customPlot->xAxis->setRange(-1, 1);
	customPlot->yAxis->setRange(1, 0);
	//TODO: Plot to Image Export ?
	//ui->customPlot->replot();

	//del memory of pointer (double[])
	delete[]values;
}



void MainWindow::realtimeDataSlot()
{
	// calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
	double key = 0;
#else
	double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
#endif
	static double lastPointKey = 0;
	if (key - lastPointKey > 0.01)	// at most add point every 10 ms
	{
		double value0 = qSin(key);	//sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
		double value1 = qCos(key);	//sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
		// add data to lines:
		ui->customPlot->graph(0)->addData(key, value0);
		ui->customPlot->graph(1)->addData(key, value1);
		// set data of dots:
		ui->customPlot->graph(2)->clearData();
		ui->customPlot->graph(2)->addData(key, value0);
		ui->customPlot->graph(3)->clearData();
		ui->customPlot->graph(3)->addData(key, value1);
		// remove data of lines that's outside visible range:
		ui->customPlot->graph(0)->removeDataBefore(key - 8);
		ui->customPlot->graph(1)->removeDataBefore(key - 8);
		// rescale value (vertical) axis to fit the current data:
		ui->customPlot->graph(0)->rescaleValueAxis();
		ui->customPlot->graph(1)->rescaleValueAxis(true);
		lastPointKey = key;
	}
	// make key axis range scroll with the data (at a constant range size of 8):
	ui->customPlot->xAxis->setRange(key + 0.25, 8, Qt::AlignRight);
	ui->customPlot->replot();

	// calculate frames per second:
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key - lastFpsKey > 2)	// average fps over 2 seconds
	{
		ui->statusBar->showMessage(QString
					   ("%1 FPS, Total Data points: %2")
					   .arg(frameCount / (key - lastFpsKey),
						0, 'f', 0)
					   .arg(ui->customPlot->graph(0)->
						data()->count() +
						ui->customPlot->graph(1)->
						data()->count())
					   , 0);
		lastFpsKey = key;
		frameCount = 0;
	}
}

void MainWindow::bracketDataSlot()
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
	double secs = 0;
#else
	double secs = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;
#endif

	// update data to make phase move:
	int n = 500;
	double phase = secs * 5;
	double k = 3;
	QVector < double >x(n), y(n);
	for (int i = 0; i < n; ++i) {
		x[i] = i / (double)(n - 1) * 34 - 17;
		y[i] = qExp(-x[i] * x[i] / 20.0) * qSin(k * x[i] + phase);
	}
	ui->customPlot->graph()->setData(x, y);

	itemDemoPhaseTracer->setGraphKey((8 * M_PI +
					  fmod(M_PI * 1.5 - phase,
					       6 * M_PI)) / k);

	ui->customPlot->replot();

	// calculate frames per second:
	double key = secs;
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key - lastFpsKey > 2)	// average fps over 2 seconds
	{
		ui->statusBar->showMessage(QString
					   ("%1 FPS, Total Data points: %2")
					   .arg(frameCount / (key - lastFpsKey),
						0, 'f', 0)
					   .arg(ui->customPlot->graph(0)->
						data()->count())
					   , 0);
		lastFpsKey = key;
		frameCount = 0;
	}
}

void MainWindow::setupPlayground(QCustomPlot * customPlot)
{
	Q_UNUSED(customPlot)
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QPixmap pm =
	    QPixmap::grabWindow(qApp->desktop()->winId(), this->x() + 20,
				this->y() + 20,
				this->frameGeometry().width() - 4,
				this->frameGeometry().height() - 4);
#else
	QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(),
						       this->x() + 2,
						       this->y() + 2,
						       this->frameGeometry().
						       width() - 4,
						       this->frameGeometry().
						       height() - 4);
	//QPixmap pm2 = qApp->primaryScreen()->grabWindow(

#endif

    QString fileName = demoName.toLower() + ".png";
	fileName.replace(" ", "");
	pm.save("/tmp/qt/" + fileName);
	qApp->quit();
}

void MainWindow::allScreenShots()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QPixmap pm =
	    QPixmap::grabWindow(qApp->desktop()->winId(), this->x() + 20,
				this->y() + 20,
				this->frameGeometry().width() - 90,
				this->frameGeometry().height() - 90);
#else
	QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(),
						       this->x() + 2,
						       this->y() + 25,
						       this->frameGeometry().
						       width() - 4,
						       this->frameGeometry().
						       height() - 40);
#endif

    if (cnt < maxpics) {
		cnt++;
		// QString fileName = demoName.toLower() + ".png";
		QString scnt = QString::number(cnt);
		int remain = 3 - scnt.length();
		for (int i = 0; i < remain; i++)
			scnt = "0" + scnt;

		QString fileName = scnt + ".png";
		fileName.replace(" ", "");
		pm.save("/tmp/" + fileName);
		//if (currentRow < 10){
		if (dataTimer.isActive())
			dataTimer.stop();
		dataTimer.disconnect();
		delete ui->customPlot;
		ui->customPlot = new QCustomPlot(ui->centralWidget);
		ui->verticalLayout->addWidget(ui->customPlot);
		//plotData(currentRow+1);
		setupGLPDemo(ui->customPlot);
		//setupDemo(currentDemoIndex + 1);
		// setup delay for demos that need time to develop proper look:

		QTimer::singleShot(delay, this, SLOT(allScreenShots()));
	} else {
    //	qApp->quit();
	}
}
