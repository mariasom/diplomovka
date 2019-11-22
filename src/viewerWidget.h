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


class viewerWidget : public QWidget {
	Q_OBJECT

public:
	viewerWidget(QWidget *parent = Q_NULLPTR);
	~viewerWidget();

	QVTKOpenGLNativeWidget* getQVTKwidget() { return qW; };
	void setAreaSize(QSize s) { qW->resize(s.width(), s.height()); }
	void setScrollArea();
	void setViewerWidget(vtkSmartPointer<vtkImageData> image, QString fName);
	QScrollArea *getScrollArea() { return _scrollArea; }
	void updateViewerWidget();

private:
	QVTKOpenGLNativeWidget* qW;
	QScrollArea* _scrollArea;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkActor> actor;

	//public slots:

};
