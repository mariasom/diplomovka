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

#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>

#include <vtkOutlineFilter.h>
#include <vtkProperty.h>
#include <vtkTexture.h>

#include <vtkShepardMethod.h>
#include <vtkProbeFilter.h>

#include <vtkFloatArray.h>

#include <vtkTransformPolyDataFilter.h>
#include <vtkVoxelContoursToSurfaceFilter.h>
#include <vtkTransform.h>

#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

#include <vtkPropPicker.h>
#include <vtkSphereSource.h>

#include <vtkHoverWidget.h>
#include <vtkCommand.h>

#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>

#include <vtkImageResliceMapper.h>

#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkPropAssembly.h>

#include <vtkCubeAxesActor.h>
#include <vtkCamera.h>

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
	//void setViewerWidget2D(vtkSmartPointer<vtkPolyData> polyData, QString fName);
	QScrollArea *getScrollArea2D() { return _scrollArea2D; }
	QScrollArea *getScrollArea3D() { return _scrollArea3D; }
	QScrollArea *getScrollArea() { return _scrollArea; }
	void updateViewerWidget2D();
	void updateViewerWidget3D();
	void updateViewerWidget();
	void setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata);
	void setViewerWidget(vtkSmartPointer<vtkImageData> image);
	void resetCam(bool dimensions);
	void set2DView(bool dimensions);
	void set3DView(bool dimensions);
	void contours3D(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background = true);
	void contours2D(vtkSmartPointer<vtkImageData> image, bool background = true);
	void saveScreenShot(bool dimensions);
	void hoverContour(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background = true);
	void addAxes(vtkSmartPointer<vtkPolyData> polydata);
	void removeAxes();

private:
	vtkSmartPointer<vtkInteractorStyleImage> imageStyle;

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
	vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor;

	//global variables for other functions.
	QVTKOpenGLNativeWidget* qW;
	QScrollArea* _scrollArea;
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkActor> actor;

	// other
	bool axes = false;
};


/*class MouseInteractorStyle2 : public vtkInteractorStyleTrackballCamera
{
public:
	static MouseInteractorStyle2* New();
	vtkTypeMacro(MouseInteractorStyle2, vtkInteractorStyleTrackballCamera);

	virtual void OnLeftButtonDown() override
	{
		int* clickPos = this->GetInteractor()->GetEventPosition();

		// Pick from this location.
		vtkSmartPointer<vtkPropPicker>  picker =
			vtkSmartPointer<vtkPropPicker>::New();
		picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

		double* pos = picker->GetPickPosition();
		std::cout << "Pick position (world coordinates) is: "
			<< pos[0] << " " << pos[1]
			<< " " << pos[2] << std::endl;

		std::cout << "Picked actor: " << picker->GetActor() << std::endl;
		//Create a sphere
		vtkSmartPointer<vtkSphereSource> sphereSource =
			vtkSmartPointer<vtkSphereSource>::New();
		sphereSource->SetCenter(pos[0], pos[1], pos[2]);
		sphereSource->SetRadius(0.1);

		//Create a mapper and actor
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(sphereSource->GetOutputPort());

		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);

		this->GetDefaultRenderer()->AddActor(actor);
		// Forward events
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}

private:

};*/

class vtkHoverCallback : public vtkCommand
{
public:
	static vtkHoverCallback *New()
	{
		return new vtkHoverCallback;
	}

	vtkHoverCallback() {}

	virtual void Execute(vtkObject*, unsigned long event, void *vtkNotUsed(calldata))
	{
		switch (event)
		{
		case vtkCommand::TimerEvent:
			std::cout << "TimerEvent -> the mouse stopped moving and the widget hovered" << std::endl;
			break;
		case vtkCommand::EndInteractionEvent:
			std::cout << "EndInteractionEvent -> the mouse started to move" << std::endl;
			break;
		}
	}
};