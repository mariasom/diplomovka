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
#include <vtkNamedColors.h>
#include <vtkImageSliceMapper.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageSlice.h>
#include <vtkImageProperty.h>
#include <vtkImageMapper.h>
#include <vtkImageViewer2.h>
#include <vtkDataSetMapper.h>
#include <vtkImageReslice.h>
#include <vtkImageInterpolator.h>
#include <vtkImageData.h>
#include <vtkWarpScalar.h>
#include <vtkCubeAxesActor2D.h>

#include <vtkAppendPolyData.h>
#include <vtkClipPolyData.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkContourFilter.h>
#include <vtkCleanPolyData.h>

#include <vtkQuadric.h>
#include <vtkSampleFunction.h>

#include <vtkXMLPolyDataWriter.h>

class viewerWidget : public QWidget {
	Q_OBJECT

public:
	viewerWidget(QWidget *parent = Q_NULLPTR);
	~viewerWidget();

	QVTKOpenGLNativeWidget* getQVTKwidget() { return qW; };
	QVTKOpenGLNativeWidget* getQVTKwidget2D() { return qW2D; };
	QVTKOpenGLNativeWidget* getQVTKwidget3D() { return qW3D; };
	void setAreaSize2D(QSize s) { qW2D->resize(s.width(), s.height()); }
	void setAreaSize3D(QSize s) { qW3D->resize(s.width(), s.height()); }
	void setAreaSize(QSize s) { qW3D->resize(s.width(), s.height()); }
	void setScrollArea2D();
	void setScrollArea3D();
	void setScrollArea();
	void setViewerWidget2D(vtkSmartPointer<vtkImageData> image, QString fName);
	//void setViewerWidget(vtkSmartPointer<vtkPolyData> polyData, QString fName);
	QScrollArea *getScrollArea2D() { return _scrollArea2D; }
	QScrollArea *getScrollArea3D() { return _scrollArea3D; }
	QScrollArea *getScrollArea() { return _scrollArea; }
	void updateViewerWidget2D();
	void updateViewerWidget3D();
	void updateViewerWidget();
	void setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata);
	void setViewerWidget(vtkSmartPointer<vtkPolyData> polydata);

private:
	//global variables for 2D data/image/threshold ect data.
	QVTKOpenGLNativeWidget* qW2D;
	QScrollArea* _scrollArea2D;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow2D;
	vtkSmartPointer<vtkRenderer> renderer2D;
	vtkSmartPointer<vtkActor> actor2D;

	//global variables for 3D distance function/subsurf ect data.
	QVTKOpenGLNativeWidget* qW3D;
	QScrollArea* _scrollArea3D;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow3D;
	vtkSmartPointer<vtkRenderer> renderer3D;
	vtkSmartPointer<vtkActor> actor3D;

	//global variables for other functions.
	QVTKOpenGLNativeWidget* qW;
	QScrollArea* _scrollArea;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkActor> actor;

	//public slots:
};
