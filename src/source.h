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
//#include <vtkPoints2D.h>
#include <vtkPolyData.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkTriangle.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToColors.h>
#include <vtkImageProperty.h>
#include <vtkInteractorStyleImage.h>
#include <vtkLookupTable.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkPNGReader.h>
#include <vtkImageViewer2.h>
#include <vtkNamedColors.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkDoubleArray.h>
#include <vtkProperty.h>
#include <vtkImageInterpolator.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkFloatArray.h>

//sing namespace std;

class source {
protected:
	QVector<unsigned char> data;
	QVector<QVector<unsigned char>> dataFilt;
	QVector<QVector<double>> data3DFilt;
	QString fileName = " ";
	int width = 0;
	int height = 0;
	int maxCol;
	bool binary = false;
	qint64 sLength = 0;
	int sSize = 0;
	QStringList file;
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkPolyData> polydata2D;
	vtkSmartPointer<vtkUnsignedCharArray> colors;
	vtkSmartPointer<vtkImageMapToColors> scalarValuesToColors;
	vtkSmartPointer<vtkLookupTable> colorLookupTable;
	vtkSmartPointer<vtkImageData> image;
	void setCol(vtkSmartPointer<vtkColorTransferFunction> color, int colorIndex);

public:
	source();
	~source();
	void load(QString path);
	void readAscii(QString path);
	void readBinary(QString path);
	QString getFileName(QString path);
	//vtkSmartPointer<vtkImageMapToColors> setPoints();
	void setPoints(QVector<unsigned char> &setData, int p = 0);
	QVector<unsigned char> getOrigData() { return  dataFilt.at(0); };
	QVector<unsigned char> getFiltData(int i) { return dataFilt.at(i); };
	QVector<double> get3DData(int i) { return data3DFilt.at(i); };
	vtkSmartPointer<vtkImageData> getImageData() { return image; };
	// vtkSmartPointer<vtkPolyData> getImageData() { return polydata2D; };
	int getWidth() { return width; };
	int getHeight() { return height; };
	vtkSmartPointer<vtkPolyData> getPolydata() { return polydata; };
	void removeFiltData(int i) { dataFilt.remove(i); };
	int getSizeFiltData() { return dataFilt.size(); };
	void remove3DData(int i) { data3DFilt.remove(i); };
	int getSize3DData() { return data3DFilt.size(); };
	void create3Ddata(QVector<double> z);

	void addFiltData(QVector<unsigned char> &addData);
	void add3DData(QVector<double> &addData);
	void save_ascii(QString fileName, int index);
	void saveVtk3D(QString fileName, int index, bool binary);
	void saveVtk2D(QString fileName, int index, bool binary);
	void colorPolyData(int colorIndex);
	void displayOnPlane(vtkSmartPointer<vtkPolyData> data);
};
