#pragma once

#include <QWidget>
#include <iostream>

class filters
{
private:
	int width;
	int height;
	int hist[256];
	QVector<unsigned char> origData;
	QVector<unsigned char> data;

public:
	filters();
	filters(int widthOrig, int heightOrig, QVector<unsigned char> oData);
	~filters();
	void histogram();
	QVector<unsigned char> getFiltDat() { return data; };
	void otsuFilter();
};