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

private:
	QVTKOpenGLNativeWidget* qW;
	QScrollArea* _scrollArea;

	//public slots:

};
