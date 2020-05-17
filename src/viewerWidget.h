#pragma once

#include <QtWidgets>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyData.h>
#include <vtkNamedColors.h>
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
#include <vtkSampleFunction.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkOutlineFilter.h>
#include <vtkProperty.h>
#include <vtkShepardMethod.h>
#include <vtkProbeFilter.h>
#include <vtkFloatArray.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkVoxelContoursToSurfaceFilter.h>
#include <vtkTransform.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkPropPicker.h>
#include <vtkCommand.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>
#include <vtkCubeAxesActor.h>
#include <vtkCamera.h>
#include <vtkTextProperty.h>
#include <vtkInteractorStyleJoystickCamera.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageDataGeometryFilter.h>

class viewerWidget : public QWidget {
	Q_OBJECT

public:
	viewerWidget(QWidget *parent = Q_NULLPTR);
	~viewerWidget();

	QVTKOpenGLNativeWidget* getQVTKwidget() { return qW; };
	void setAreaSize(QSize s) { qW->resize(s.width(), s.height()); }
	void setScrollArea();
	void setViewerWidget2D(vtkSmartPointer<vtkPolyData> polyData, QString fName);
	QScrollArea *getScrollArea() { return _scrollArea; }
	void updateViewerWidget2D();
	void updateViewerWidget3D();
	void setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata);
	void resetCam();
	void set2DView();
	void set3DView();
	void contours3D(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background = true);
	void contours2D(vtkSmartPointer<vtkPolyData> image, bool background = true);
	void saveScreenShot(QString fileName);
	void cutContour(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background = true);
	void addAxes(vtkSmartPointer<vtkPolyData> polydata);
	void removeAxes();
	void cut1Contour(vtkSmartPointer<vtkPolyData> polydata, double zValue, bool onOgdata = false);
	void optContourOnID(double zValue);

private:
	QVTKOpenGLNativeWidget* qW;
	QScrollArea* _scrollArea;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkActor> actor;
	vtkSmartPointer<vtkActor> actor3D;
	vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor;
	vtkSmartPointer<vtkActor> cutterActor;
	vtkSmartPointer<vtkActor> actor2D;
	vtkSmartPointer<vtkInteractorStyleImage> imageStyle2D;
	vtkSmartPointer<vtkInteractorStyleJoystickCamera> imageStyle3D;

	// other variables
	bool axes = false;
	double bounds[6];
};