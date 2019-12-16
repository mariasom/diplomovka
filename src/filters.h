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

	QVector<unsigned char> reflection(QVector<unsigned char> edge, int p);


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
	void distFunct();
	void DistFunctSign();
	QVector<QVector<float>> makeTables(int K, QVector<float> histN);
};