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
	QVector<int> hist;
	QVector<unsigned char> origData;
	QVector<unsigned char> newData;
	QVector<QVector<int>> t;


public:
	filters();
	filters(int widthOrig, int heightOrig, QVector<unsigned char> oData);
	~filters();
	void histogram();
	QVector<unsigned char> getFiltDat() { return newData; };
	void otsuFilter();
	void kapuraFilter();
	void coOcMatrix();
	QVector<QVector<float>> makeTables(int K, QVector<float> histN);
};