#pragma once
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <iostream>
#include <fstream>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkTriangle.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkDoubleArray.h>
#include <vtkProperty.h>
#include <vtkImageInterpolator.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkFloatArray.h>
#include <vtkLine.h>
#include <vtkPolygon.h>
#include <vtkTIFFReader.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageData.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkDataArray.h>

class source {
protected:
	QVector<unsigned char> data;
	QVector<QVector<unsigned char>> dataFilt;
	QVector<QVector<double>> data3DFilt;
	QVector<double> zMin;
	QVector<double> zMax;
	QString fileName = " ";
	double bounds[6];
	int width = 0;
	int height = 0;
	int maxCol;
	bool binary = false;
	qint64 sLength = 0;
	int sSize = 0;
	QStringList file;
	QString info;
	vtkSmartPointer<vtkPoints> points2D;
	vtkSmartPointer<vtkPoints> points3D;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkPolyData> polydata2D;
	vtkSmartPointer<vtkUnsignedCharArray> colors;
	vtkSmartPointer<vtkImageMapToColors> scalarValuesToColors;
	vtkSmartPointer<vtkLookupTable> colorLookupTable;
	void setCol(vtkSmartPointer<vtkColorTransferFunction> color, int colorIndex);
	vtkSmartPointer<vtkImageDataGeometryFilter> imageDataGeometryFilter;

	void setText(QString text);
	void addZMinandMax();

public:
	source();
	~source();
	vtkSmartPointer<vtkPolyData> getPolydata() { return polydata; };
	QVector<unsigned char> getOrigData() { return  dataFilt.at(0); };
	QVector<unsigned char> getFiltData(int i) { return dataFilt.at(i); };
	QVector<double> get3DData(int i) { return data3DFilt.at(i); };
	vtkSmartPointer<vtkPolyData> getImageData() { return polydata2D; };
	vtkSmartPointer<vtkImageDataGeometryFilter> getTIFFPolydata() { return imageDataGeometryFilter; };
	int getSizeFiltData() { return dataFilt.size(); };
	int getSize3DData() { return data3DFilt.size(); };
	int getWidth() { return width; };
	int getHeight() { return height; };
	double getZMin(int i) { return zMin.at(i); };
	double getZMax(int i) { return zMax.at(i); };
	QString getText() { return info; };
	QString getFileName(QString path);

	// file load
	void load(QString path);
	void readTifFile(QString path);
	void readAscii(QString path);
	void readBinary(QString path);
	
	//create polydata 
	void setPoints(QVector<unsigned char> &setData, int p = 0);
	void create3Ddata(QVector<double> z);
	void colorPolyData(int colorIndex);
	void setNewDataWin(QVector<unsigned char> dataToSet, int h, int w);

	//data maniulation
	void remove2DFiltData(int i) { dataFilt.remove(i); };
	void remove3DFiltData(int i) { data3DFilt.remove(i); };
	void addFiltData(QVector<unsigned char> &addData);
	void add3DData(QVector<double> &addData);

	// save to file
	void save_ascii(QString fileName, int index);
	void saveVtk3D(QString fileName, int index, bool binary);
	void saveVtk2D(QString fileName, int index, bool binary);
	void saveHistOutput(QString text, QString fileName);
};
