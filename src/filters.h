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
	QVector<unsigned char> origData;
	QVector<unsigned char> newData;
	QVector<QVector<int>> t;
	QVector<unsigned char> aw(QVector<unsigned char> data, bool eps);
	QVector<unsigned char> an(QVector<unsigned char> data, bool eps);
	QVector<unsigned char> as(QVector<unsigned char> data, bool eps);
	QVector<unsigned char> ae(QVector<unsigned char> data, bool eps);
	double M(QVector<unsigned char> u,int i, int j, int p, int q);
	double findmax(double m1, double m2);
	QVector<unsigned char> heatImpl(QVector<unsigned char> data);
	QVector<unsigned char> antireflection(QVector<unsigned char> data, int p = 1);
	QVector<unsigned char> reflection(QVector<unsigned char> data, int p = 1);


public:
	filters();
	filters(int widthOrig, int heightOrig, QVector<unsigned char> oData);
	~filters();
	void histogram();
	QVector<unsigned char> getFiltDat() { return newData; };
	void otsuFilter();
	void kapuraFilter();
	void coOcMatrix();
	void boundary();
	void createNewData();
	QVector<unsigned char> distFunct(QVector<unsigned char> data);
	QVector<unsigned char> distFunctSign(QVector<unsigned char> data);
	QVector<QVector<float>> makeTables(int K, QVector<float> histN);
	QVector<unsigned char> subSurf(QVector<unsigned char> data);
};