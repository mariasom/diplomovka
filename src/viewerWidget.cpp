#include "viewerWidget.h"

viewerWidget::viewerWidget(QWidget *parent) : QWidget(parent) {
	setAttribute(Qt::WA_StaticContents);
	qW2D = new QVTKOpenGLNativeWidget(this);
	qW3D = new QVTKOpenGLNativeWidget(this);

	imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
}

viewerWidget::~viewerWidget() {
}

void viewerWidget::setScrollArea2D() {
	_scrollArea2D = new QScrollArea;
	_scrollArea2D->setObjectName("QScrollArea");
	_scrollArea2D->setWidget(qW2D);
	_scrollArea2D->setBackgroundRole(QPalette::Dark);
	_scrollArea2D->setWidgetResizable(true);
	_scrollArea2D->installEventFilter(this);
	_scrollArea2D->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_scrollArea2D->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void viewerWidget::setScrollArea3D() {
	_scrollArea3D = new QScrollArea;
	_scrollArea3D->setObjectName("QScrollArea");
	_scrollArea3D->setWidget(qW3D);
	_scrollArea3D->setBackgroundRole(QPalette::Dark);
	_scrollArea3D->setWidgetResizable(true);
	_scrollArea3D->installEventFilter(this);
	_scrollArea3D->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_scrollArea3D->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

/*void viewerWidget::setViewerWidget(vtkSmartPointer<vtkPolyData> polyData, QString fName)
{
	qW->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polyData);
	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor);
	//renderer->AddActor(scalarBar);
	renderer->SetBackground(1, 1, 1);
	//renderer->AddViewProp(cornerAnnotation(fName));

	// VTK/Qt wedded
	qW->GetRenderWindow()->AddRenderer(renderer);
}*/
// void viewerWidget::setViewerWidget2D(vtkSmartPointer<vtkPolyData> image, QString fName) {
void viewerWidget::setViewerWidget2D(vtkSmartPointer<vtkImageData> image, QString fName) {

	//vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	qW2D->SetRenderWindow(renderWindow2D);

	// vtkSmartPointer<vtkInteractorStyleImage> imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
	//imageStyle->SetInteractionMode(1);
	imageStyle->SetInteractionModeToImage2D();
	//imageStyle->StartRotate();
	//std::cout << imageStyle->GetInteractionMode() << std::endl;
	qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);

	/*vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(image);

	actor2D = vtkSmartPointer<vtkActor>::New();
	actor2D->SetMapper(mapper);

	renderer2D = vtkSmartPointer<vtkRenderer>::New();
	renderWindow2D->AddRenderer(renderer2D);

	renderer2D->GetViewProps()->RemoveAllItems();
	renderer2D->AddActor(actor2D);
	renderer2D->SetBackground(1, 1, 1);
	renderer2D->ResetCamera();*/

	//vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputData(image);
	//reslice->SetOutputSpacing(0);
	//reslice->SetInterpolate(0);
	//reslice->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->InterpolateScalarsBeforeMappingOn();
	// mapper->SetInputData(reslice->GetOutput());
	mapper->SetInputData(image);

	actor2D = vtkSmartPointer<vtkActor>::New();
	actor2D->SetMapper(mapper);

	renderer2D = vtkSmartPointer<vtkRenderer>::New();

	renderWindow2D->AddRenderer(renderer2D);
	renderer2D->AddActor(actor2D);
	renderer2D->SetBackground(1, 1, 1);
	renderer2D->ResetCamera();

	qW2D->GetRenderWindow()->AddRenderer(renderer2D);
}

void viewerWidget::updateViewerWidget2D() {
	renderer2D->GetViewProps()->RemoveAllItems();
	renderer2D->AddActor(actor2D);
	renderer2D->SetBackground(1, 1, 1);
	renderWindow2D->Render();
}

void viewerWidget::updateViewerWidget3D() {
	renderer3D->GetViewProps()->RemoveAllItems();
	renderer3D->AddActor(actor3D);
	renderer3D->SetBackground(0,0,0);
	renderWindow3D->Render();
}

void viewerWidget::setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata) {
	qW3D->SetRenderWindow(renderWindow3D);
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polydata);

	actor3D = vtkSmartPointer<vtkActor>::New();
	actor3D->SetMapper(mapper);

	renderer3D = vtkSmartPointer<vtkRenderer>::New();
	renderWindow3D->AddRenderer(renderer3D);

	renderer3D->GetViewProps()->RemoveAllItems();
	renderer3D->AddActor(actor3D);
	renderer3D->SetBackground(.1, .2, .3);

	/*vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow3D);

	vtkSmartPointer<vtkAxesActor> axes =
		vtkSmartPointer<vtkAxesActor>::New();

	vtkSmartPointer<vtkOrientationMarkerWidget> widget =
		vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	widget->SetOrientationMarker(axes);
	widget->SetInteractor(renderWindowInteractor);
	widget->SetViewport(0.0, 0.0, 0.4, 0.4);
	widget->SetEnabled(1);
	widget->InteractiveOn();

	// renderer3D->ResetCamera();*/

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);
}

void viewerWidget::setViewerWidget() {

	
	//imageStyle->SetInteractionMode(1);
	imageStyle->SetInteractionModeToImageSlicing();
	//imageStyle->StartRotate();
	//std::cout << imageStyle->GetInteractionMode() << std::endl;
	qW3D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);

	// Sample quadric function
	// vtkSmartPointer<vtkQuadric> quadric = vtkSmartPointer<vtkQuadric>::New();
	// quadric->SetCoefficients(1, 2, 3, 0, 1, 0, 0, 0, 0, 0);

	// vtkSmartPointer<vtkSampleFunction> sample = vtkSmartPointer<vtkSampleFunction>::New();
	// sample->SetSampleDimensions(40, 40, 40);
	// sample->SetImplicitFunction(quadric);

	// Generate implicit surface
	/*vtkSmartPointer <vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputData(sample->GetOutput());
	double range[2];
	range[0] = 1.0; range[1] = 6.0;
	contour->GenerateValues(3, range);

	// Map contour
	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputData(contour->GetOutput());
	contourMapper->SetScalarRange(0, 7);

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);


	/*vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputData(polydata);
	// contour->SetInputConnection();
	contour->SetValue(0,1.2);

	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	// contourMapper->SetInputData(contour->GetOutput());
	// contourMapper->SetInputConnection(contour->GetOutputPort());
	contourMapper->SetScalarRange(polydata->GetScalarRange());
	//polydata->GetScalarRange();

	vtkSmartPointer <vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);*/

	/*vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(sample->GetOutput(0));

	actor3D = vtkSmartPointer<vtkActor>::New();
	actor3D->SetMapper(mapper);

	renderer3D = vtkSmartPointer<vtkRenderer>::New();
	renderWindow3D->AddRenderer(renderer3D);

	renderer3D->GetViewProps()->RemoveAllItems();
	renderer3D->AddActor(actor3D);
	renderer3D->SetBackground(1.0, 1.0, 1.0);

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);

	/*qW->SetRenderWindow(renderWindow);

	// warp plane
	vtkSmartPointer<vtkWarpScalar> warp = vtkSmartPointer<vtkWarpScalar>::New();
	warp->SetInputData(polydata);
	warp->SetScaleFactor(0.0);

	// Visualize
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(warp->GetOutputPort());

	actor = vtkSmartPointer<vtkActor>::New();
	//actor->GetProperty()->SetPointSize(4);
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow3D->AddRenderer(renderer3D);

	renderer3D->GetViewProps()->RemoveAllItems();
	renderer3D->AddActor(actor3D);
	renderer3D->SetBackground(.1, .2, .3);
 

	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3);
	renderWindow->Render();

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	//qW->GetRenderWindow()->SetInteractorStyle(style);

	// add & render CubeAxes
	vtkSmartPointer<vtkCubeAxesActor2D> axes = vtkSmartPointer<vtkCubeAxesActor2D>::New();
	axes->SetInputData(warp->GetOutput());
	axes->SetFontFactor(3.0);
	axes->SetFlyModeToNone();
	axes->SetCamera(renderer->GetActiveCamera());

	vtkSmartPointer<vtkAxisActor2D> xAxis = axes->GetXAxisActor2D();
	//xAxis->SetAdjustLabels(1);
	renderer->AddViewProp(axes);

	qW3D->GetRenderWindow()->AddRenderer(renderer);*/
}

void viewerWidget::resetCam(bool dimensions) {
	if (dimensions) {
		renderer2D->ResetCamera();
		renderWindow2D->Render();
	}
	else {
		renderer3D->ResetCamera();
		renderWindow3D->Render();
	}
}

void viewerWidget::set2DView(bool dimensions) {
	if (dimensions) {
		imageStyle->SetInteractionModeToImage2D();
		qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
	}
	else {
		imageStyle->SetInteractionModeToImage2D();
		qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
	}
}

void viewerWidget::set3DView(bool dimensions) {
	if (dimensions) {
		imageStyle->SetInteractionModeToImage3D();
		qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
	}
	else {
		imageStyle->SetInteractionModeToImage3D();
		qW3D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
	}
}