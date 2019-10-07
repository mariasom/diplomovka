#pragma once
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <iostream>

using namespace std;

class source {
protected:
	QVector<int> data;
	QString fileName = " ";
	int width = 0;
	int height = 0;
	int maxCol;	

public:
	source();
	~source();
	void load(QString path);
	void readAscii(QStringList file);
	void readBinary(QStringList file);
	QString getFileName(QString path);

};