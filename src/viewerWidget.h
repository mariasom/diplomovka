#pragma once
#include <QtWidgets>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkCornerAnnotation.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyData.h>
#include <vtkTextProperty.h>
#include <vtkWindowToImageFilter.h>
#include <vtkImageWriter.h>
#include <vtkPNGWriter.h>
#include <vtkProperty.h>
#include <vtkScalarBarActor.h>
#include <vtkLookupTable.h>
#include <vtkCamera.h>

class viewerWidget : public QWidget {
	Q_OBJECT

public:
	viewerWidget(QWidget *parent = Q_NULLPTR);
	~viewerWidget();

	QVTKOpenGLNativeWidget* getQVTKwidget() { return qW; };
	void setAreaSize(QSize s) { qW->resize(s.width(), s.height()); }
	void setScrollArea();
	void setViewerWidget(vtkSmartPointer<vtkPolyData> polyData, QString fName);
	//void updateViewerWidget(vtkSmartPointer<vtkPolyData> polyData, QString fName, QString filterInfo = NULL, bool scale = false);
	QScrollArea *getScrollArea() { return _scrollArea; }
	//void resetCamera(int width, int height);
	//vtkSmartPointer<vtkScalarBarActor> setScalarBar(vtkSmartPointer<vtkScalarBarActor> scalarbar);

private:
	QVTKOpenGLNativeWidget* qW;
	QScrollArea* _scrollArea;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkScalarBarActor> scalarBar;
	vtkSmartPointer<vtkLookupTable> hue_Lut;
	QString filterInfoOld;

	//public slots:

};
