#include "viewerWidget.h"

// vtkStandardNewMacro(MouseInteractorStyle2);

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

	//vtkSmartPointer<vtkInteractorStyleImage> imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
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
	renderer3D->SetBackground(.1, .2, .3);
	renderWindow3D->Render();
}

void viewerWidget::setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata) {
	qW3D->SetRenderWindow(renderWindow3D);
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	//mapper->ScalarVisibilityOff();
	mapper->SetInputData(polydata);

	actor3D = vtkSmartPointer<vtkActor>::New();
	actor3D->SetMapper(mapper);

	renderer3D = vtkSmartPointer<vtkRenderer>::New();
	renderWindow3D->AddRenderer(renderer3D);

	renderer3D->GetViewProps()->RemoveAllItems();
	renderer3D->AddActor(actor3D);
	renderer3D->SetBackground(.1, .2, .3);

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);
}

void viewerWidget::contours3D(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background) {
	qW3D->SetRenderWindow(renderWindow3D);

	double bounds[6];
	polydata->GetBounds(bounds);
	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputData(polydata);
	contour->GenerateTrianglesOff();
	contour->ComputeNormalsOn();

	double getRange = abs(bounds[5] - bounds[4]);
	contour->GenerateValues(numOfCont, 0, getRange*10);
	contour->GetUseScalarTree();
	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contour->GetOutputPort());
	if(background)
		contourMapper->ScalarVisibilityOff();
	contourMapper->InterpolateScalarsBeforeMappingOn();
	contourMapper->SetScalarRange(polydata->GetScalarRange());

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->GetProperty()->SetLineWidth(2);
	contourActor->SetMapper(contourMapper);

	renderer3D->GetViewProps()->RemoveAllItems();
	if(background)
		renderer3D->AddActor(actor3D);
	renderer3D->AddActor(contourActor);
	renderer3D->SetBackground(.1, .2, .3);

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);
	qW3D->GetRenderWindow()->Render();
}

void viewerWidget::contours2D(vtkSmartPointer<vtkImageData> image, bool background) {
	qW2D->SetRenderWindow(renderWindow2D);

	vtkSmartPointer<vtkContourFilter> contourFilter =
		vtkSmartPointer<vtkContourFilter>::New();
	contourFilter->SetInputData(image);
	contourFilter->GenerateValues(1, 10, 10);

	// contours for the macrophages
	vtkSmartPointer<vtkPolyDataMapper> contourMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contourFilter->GetOutputPort());

	//Create an actor for the contours
	vtkSmartPointer<vtkActor> contourActor =
		vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);
	contourMapper->ScalarVisibilityOff();
	contourActor->GetProperty()->SetColor(1, 0, 0);
	contourActor->GetProperty()->SetLineWidth(2);

	// Create the outline
	vtkSmartPointer<vtkOutlineFilter> outlineFilter =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outlineFilter->SetInputData(image);

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());

	//Create an actor for the outline
	vtkSmartPointer<vtkActor> outlineActor =
		vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(1, 0.5, 0);
	outlineActor->GetProperty()->SetLineWidth(2);

	renderer2D->GetViewProps()->RemoveAllItems();
	if(background) 
		renderer2D->AddActor(actor2D);
	else
		renderer2D->AddActor(outlineActor);
	renderer2D->AddActor(contourActor);
    renderWindow2D->Render();
	renderer2D->ResetCamera();

	qW2D->GetRenderWindow()->AddRenderer(renderer2D);

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
		renderWindow2D->Render();
	}
	else {
		imageStyle->SetInteractionModeToImage2D();
		qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
		renderWindow3D->Render();
	}
}

void viewerWidget::set3DView(bool dimensions) {
	if (dimensions) {
		imageStyle->SetInteractionModeToImage3D();
		qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
		renderWindow2D->Render();
	}
	else {
		imageStyle->SetInteractionModeToImage3D();
		qW3D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
		renderWindow3D->Render();
	}
}

void viewerWidget::saveScreenShot(bool dimensions) {
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
		vtkSmartPointer<vtkWindowToImageFilter>::New();
	if (dimensions)
		windowToImageFilter->SetInput(renderWindow2D);
	else 
		windowToImageFilter->SetInput(renderWindow3D);
	// windowToImageFilter->SetMagnification(3); 
	windowToImageFilter->SetInputBufferTypeToRGBA(); 
	windowToImageFilter->ReadFrontBufferOff(); 
	windowToImageFilter->Update();

	QString screenShot = QFileDialog::getSaveFileName(this, "Save file", "", ".png");
	screenShot += ".png";

	vtkSmartPointer<vtkPNGWriter> writer =
		vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetFileName(screenShot.toStdString().c_str());
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->Write();
}

void viewerWidget::hoverContour(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background) {
	qW3D->SetRenderWindow(renderWindow3D);

	double bounds[6];
	polydata->GetBounds(bounds);
	std::cout << "Bounds: "
		<< bounds[0] << ", " << bounds[1] << " "
		<< bounds[2] << ", " << bounds[3] << " "
		<< bounds[4] << ", " << bounds[5] << std::endl;

	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin((bounds[1] + bounds[0]) / 2.0,
		(bounds[3] + bounds[2]) / 2.0,
		bounds[4]);
	plane->SetNormal(0, 0, 1);
	// plane->SetOrigin(0, 0, bounds[5]);
	
	// Create cutter
	double high = plane->EvaluateFunction((bounds[1] + bounds[0]) / 2.0,
		(bounds[3] + bounds[2]) / 2.0,
		bounds[5]);

	vtkSmartPointer<vtkCutter> cutter =
		vtkSmartPointer<vtkCutter>::New();
	cutter->SetInputData(polydata);
	cutter->SetCutFunction(plane);
	cutter->GenerateValues(numOfCont, .99, .99 * high);
	cutter->SetReferenceCount(2);

	vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	cutterMapper->SetInputConnection(cutter->GetOutputPort());
	cutterMapper->ScalarVisibilityOff();

	// Create cut actor
	vtkSmartPointer<vtkActor> cutterActor =
		vtkSmartPointer<vtkActor>::New();
	//cutterActor->GetProperty()->SetColor(0,1,1);
	cutterActor->GetProperty()->SetLineWidth(2);
	cutterActor->SetMapper(cutterMapper);

	// Create plane actor
	vtkSmartPointer<vtkPlaneSource> planeSource =
		vtkSmartPointer<vtkPlaneSource>::New();
	planeSource->SetNormal(1, 0, 0);
	planeSource->SetOrigin(0, 0, -10);
	planeSource->Update();

	// Create a mapper and actor.
	vtkSmartPointer<vtkPolyDataMapper> planeSourceMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	planeSourceMapper->SetInputConnection(planeSource->GetOutputPort());

	vtkSmartPointer<vtkActor> planeSourceActor =
		vtkSmartPointer<vtkActor>::New();
	planeSourceActor->SetMapper(planeSourceMapper);

	renderer3D->GetViewProps()->RemoveAllItems();
	if (background)
		renderer3D->AddActor(actor3D);
	//renderer3D->AddActor(planeSourceActor);
	renderer3D->AddActor(cutterActor);

	renderer3D->SetBackground(.1, .2, .3);

	// Create the widget
	/*vtkSmartPointer<vtkHoverWidget> hoverWidget =
		vtkSmartPointer<vtkHoverWidget>::New();
	hoverWidget->SetInteractor(qW3D->GetRenderWindow()->GetInteractor());
	hoverWidget->SetTimerDuration(500);

	// Create a callback to listen to the widget's two VTK events
	vtkSmartPointer<vtkHoverCallback> hoverCallback =
		vtkSmartPointer<vtkHoverCallback>::New();
	hoverWidget->AddObserver(vtkCommand::TimerEvent, hoverCallback);
	hoverWidget->AddObserver(vtkCommand::EndInteractionEvent, hoverCallback);

	//hoverWidget->On();
	qW3D->GetRenderWindow()->Render();
	*/

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);
	qW3D->GetRenderWindow()->Render();
	//hoverWidget->On();
}