#pragma once
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QList>
#include <iostream>

#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
// #include <vtkPoints2D.h>
#include <vtkPolyData.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>

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


//sing namespace std;

class source {
protected:
	QVector<int> data;
	QString fileName = " ";
	int width = 0;
	int height = 0;
	int maxCol;
	QStringList file;
	vtkSmartPointer<vtkPoints> points;
	vtkSmartPointer<vtkPolyData> polydata;
	vtkSmartPointer<vtkUnsignedCharArray> colors;
	vtkSmartPointer<vtkImageMapToColors> scalarValuesToColors;
	vtkSmartPointer<vtkLookupTable> colorLookupTable;
	vtkSmartPointer<vtkImageData> image;


public:
	source();
	~source();
	void load(QString path);
	//void readAscii(QStringList file);
	//void readBinary(QStringList file);
	QString getFileName(QString path);
	//vtkSmartPointer<vtkImageMapToColors> setPoints();
	void setPoints();
	vtkSmartPointer<vtkImageData> getData() { return image; };

};