#pragma once

#include <QWidget>
#include <iostream>
#include <QtMath>
#include <math.h>

class filters
{
private:
	int width;
	int height;
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
	QVector<double> antireflection(QVector<double> data, int p = 1);
	QVector<double> updateReflection(QVector<double> data, int p = 1);
	QVector<double> pow2(QVector<double> data);




public:
	filters();
	filters(int widthOrig, int heightOrig, QVector<unsigned char> oData);
	~filters();
	void histogram(QVector<double> data);
	QVector<unsigned char> getFiltDat() { return charData; };
	int otsuFilter();
	int kapuraFilter();
	void coOcMatrix();
	QVector<double> boundary(QVector<double> data, int threshold);
	QVector<unsigned char> createNewData(QVector<unsigned char> data, int threshold);
	QVector<double> dataToDouble(QVector<unsigned char> oData);
	QVector<int> dataToInt(QVector<unsigned char> oData);
	QVector<int> dataToInt(QVector<double> oData);
	QVector<double> changeRangeOfData(QVector<int> data);
	QVector<double> changeRangeOfData(QVector<double> data, int p = 0);
	QVector<unsigned char> dataToChar(QVector<double> data);
	QVector<double> distFunct(QVector<double> data);
	QVector<double> distFunctSign(QVector<double> data);
	QVector<QVector<float>> makeTables(int K, QVector<float> histN);
	QVector<double> subSurf(QVector<double> data, QVector<double> tData);
	QVector<double> heatImpl(QVector<double> data, int p = 1);
	QVector<double> niblackThreshold(QVector<double> data, int p = 1);
	QVector<double> reflection(QVector<double> data, int p = 1);

};