#pragma once

#include <QWidget>
#include <iostream>
#include <QtMath>
#include <math.h>
#include <qfile>
#include <QTextStream>

class filters
{
private:
	int width, height, widthR, heightR, p;
	float threshold = 0;
	QVector<int> hist;
	QVector<double> origData;
	QVector<double> newData;
	QVector<unsigned char> charData;
	QVector<QVector<int>> t;
	//QVector<double> dataToDouble(QVector<unsigned char> oData);
	QVector<double> aw(QVector<double> data, bool eps);
	QVector<double> an(QVector<double> data, bool eps);
	QVector<double> as(QVector<double> data, bool eps);
	QVector<double> ae(QVector<double> data, bool eps);
	double M(QVector<double> u,int i, int j, int p, int q);
	double findmax(double m1, double m2);
	QVector<double> antireflection(QVector<double> data);
	QVector<double> updateReflection(QVector<double> data);
	QVector<double> pow2(QVector<double> data);
	// void tmp_save(QString fileName, QVector<double> data, int w, int h);


public:
	filters();
	filters(int widthOrig, int heightOrig, QVector<unsigned char> oData, int pp = 1);
	~filters();
	void histogram(QVector<double> data);
	QVector<unsigned char> getFiltDat() { return charData; };
	int otsuFilter();
	int kapuraFilter();
	QVector<double> boundary(QVector<double> data, int threshold = -1);
	QVector<unsigned char> createNewData(QVector<unsigned char> data, int threshold);
	QVector<double> dataToDouble(QVector<unsigned char> oData);
	QVector<int> dataToInt(QVector<unsigned char> oData);
	QVector<int> dataToInt(QVector<double> oData);
	QVector<double> changeRangeOfData(QVector<int> data);
	QVector<double> changeRangeOfData(QVector<double> data);
	QVector<unsigned char> dataToChar(QVector<double> data);
	QVector<double> distFunct(QVector<double> data);
	QVector<double> distFunctSign(QVector<double> data);
	QVector<QVector<float>> makeTables(int K, QVector<float> histN);
	QVector<double> subSurf(QVector<double> data, QVector<double> tData, double sigma, double tau, double k); //sigma - size of lin. time steps, tau - nonlinear time steps, k - sensitivity coeficient
	QVector<double> heatImpl(QVector<double> data, double timeStep);
	QVector<double> niblackThreshold(QVector<double> data, double timeStep);
	QVector<double> reflection(QVector<double> data);
	QVector<double> thresholdFunction(QVector<unsigned char> initConData);
	QVector<double> bernsenThreshold(QVector<double> data);
	QVector<unsigned char> dataDifference(QVector<unsigned char> tData);
};