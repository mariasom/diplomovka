#include "viewerWidget.h"

viewerWidget::viewerWidget(QWidget *parent) : QWidget(parent) {
	setAttribute(Qt::WA_StaticContents);
	qW = new QVTKOpenGLNativeWidget(this);
	imageStyle2D = vtkSmartPointer<vtkInteractorStyleImage>::New();
	imageStyle3D = vtkSmartPointer<vtkInteractorStyleJoystickCamera>::New();
	cutterActor = vtkSmartPointer<vtkActor>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
}

viewerWidget::~viewerWidget() {
}

void viewerWidget::setScrollArea() {
	_scrollArea = new QScrollArea;
	_scrollArea->setObjectName("QScrollArea");
	_scrollArea->setWidget(qW);
	_scrollArea->setBackgroundRole(QPalette::Dark);
	_scrollArea->setWidgetResizable(true);
	_scrollArea->installEventFilter(this);
	_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void viewerWidget::setViewerWidget2D(vtkSmartPointer<vtkPolyData> image, QString fName) {
	qW->SetRenderWindow(renderWindow);

	image->GetBounds(bounds);
	std::cout << image->GetNumberOfPoints() << endl;
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->ClearColorArrays();
	mapper->SetInputData(image);
	mapper->InterpolateScalarsBeforeMappingOn();
	actor2D = vtkSmartPointer<vtkActor>::New();
	actor2D->SetMapper(mapper);

	renderer->GetViewProps()->RemoveAllItems();
	renderWindow->AddRenderer(renderer);
	renderer->AddActor(actor2D);
	renderer->SetBackground(1,1, 1);
	renderer->ResetCamera();

	qW->GetRenderWindow()->AddRenderer(renderer);
	qW->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle2D);
}

void viewerWidget::updateViewerWidget2D() {
	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor2D);
	renderer->SetBackground(1, 1, 1);
	renderWindow->Render();
}

void viewerWidget::updateViewerWidget3D() {
	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor3D);
	if(axes)
		renderer->AddActor(cubeAxesActor);
	renderer->SetBackground(.1, .2, .3);
	renderWindow->Render();
}

void viewerWidget::setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata) {
	qW->SetRenderWindow(renderWindow);

	polydata->GetBounds(bounds);
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polydata);

	actor3D = vtkSmartPointer<vtkActor>::New();
	actor3D->SetMapper(mapper);

	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor3D);
	renderer->SetBackground(.1, .2, .3);
	if (axes)
		addAxes(polydata);
	renderer->ResetCamera();

	qW->GetRenderWindow()->AddRenderer(renderer);
	renderWindow->Render();
	qW->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle3D);
}

void viewerWidget::contours3D(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background) {
	qW->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkContourFilter> contour = 
		vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputData(polydata);
	contour->GenerateTrianglesOff();
	contour->ComputeNormalsOn();

	double getRange = abs(bounds[5] - bounds[4]);
	contour->GenerateValues(numOfCont, 0, getRange*10);
	contour->GetUseScalarTree();
	vtkSmartPointer<vtkPolyDataMapper> contourMapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contour->GetOutputPort());
	if(background)
		contourMapper->ScalarVisibilityOff();
	contourMapper->InterpolateScalarsBeforeMappingOn();
	contourMapper->SetScalarRange(polydata->GetScalarRange());

	vtkSmartPointer<vtkActor> contourActor = 
		vtkSmartPointer<vtkActor>::New();
	contourActor->GetProperty()->SetLineWidth(2);
	contourActor->SetMapper(contourMapper);

	renderer->GetViewProps()->RemoveAllItems();	renderer->GetViewProps()->RemoveAllItems();
	if(background)
		renderer->AddActor(actor3D);
	renderer->AddActor(contourActor);
	renderer->SetBackground(.1, .2, .3);
	if (axes)
		addAxes(polydata);
	renderer->ResetCamera();

	qW->GetRenderWindow()->AddRenderer(renderer);
	qW->GetRenderWindow()->Render();
}

void viewerWidget::contours2D(vtkSmartPointer<vtkPolyData> image, bool background) {
	qW->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkContourFilter> contourFilter =
		vtkSmartPointer<vtkContourFilter>::New();
	contourFilter->SetInputData(image);
	contourFilter->GenerateValues(1, 10, 10);

	vtkSmartPointer<vtkPolyDataMapper> contourMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contourFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> contourActor =
		vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);
	contourMapper->ScalarVisibilityOff();
	contourActor->GetProperty()->SetColor(1, 0, 0);
	contourActor->GetProperty()->SetLineWidth(2);

	vtkSmartPointer<vtkOutlineFilter> outlineFilter =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outlineFilter->SetInputData(image);

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());

	vtkSmartPointer<vtkActor> outlineActor =
		vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(1, 0.5, 0);
	outlineActor->GetProperty()->SetLineWidth(2);

	renderer->GetViewProps()->RemoveAllItems();
	if(background) 
		renderer->AddActor(actor2D);
	else
		renderer->AddActor(outlineActor);
	renderer->AddActor(contourActor);
    renderWindow->Render();
	renderer->ResetCamera();

	qW->GetRenderWindow()->AddRenderer(renderer);
}

void viewerWidget::resetCam() {
	renderer->GetActiveCamera()->SetPosition((bounds[1] - bounds[0])/2.0, (bounds[3] - bounds[2]), (bounds[1] - bounds[0])*(bounds[3] - bounds[2]));
	renderer->GetActiveCamera()->SetViewUp(0, 1, 0);
	renderer->ResetCamera();
	renderWindow->Render();
}

void viewerWidget::set2DView() {
		qW->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle2D);
		renderWindow->Render();
}

void viewerWidget::set3DView() {
		renderWindow->Render();
		qW->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle3D);
}

void viewerWidget::saveScreenShot(QString fileName) {
	vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter =
		vtkSmartPointer<vtkWindowToImageFilter>::New();
	windowToImageFilter->SetInput(renderWindow);
	windowToImageFilter->SetInputBufferTypeToRGBA(); 
	windowToImageFilter->ReadFrontBufferOff(); 
	windowToImageFilter->Update();

	vtkSmartPointer<vtkPNGWriter> writer =
		vtkSmartPointer<vtkPNGWriter>::New();
	writer->SetFileName(fileName.toStdString().c_str());
	writer->SetInputConnection(windowToImageFilter->GetOutputPort());
	writer->Write();
}

void viewerWidget::cutContour(vtkSmartPointer<vtkPolyData> polydata, int numOfCont, bool background) {
	qW->SetRenderWindow(renderWindow);
	polydata->GetBounds(bounds);

	// mozno upravit ak zvysi cas
	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin((bounds[1] + bounds[0]) / 2.0,
		(bounds[3] + bounds[2]) / 2.0,
		bounds[4]);
	plane->SetNormal(0, 0, 1);

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

	cutterActor->GetProperty()->SetLineWidth(2);
	cutterActor->SetMapper(cutterMapper);
	cutterActor->GetProperty()->SetColor(1, 0, 0);

	vtkSmartPointer<vtkPlaneSource> planeSource =
		vtkSmartPointer<vtkPlaneSource>::New();
	planeSource->SetNormal(1, 0, 0);
	planeSource->SetOrigin(0, 0, -10);
	planeSource->Update();

	vtkSmartPointer<vtkPolyDataMapper> planeSourceMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	planeSourceMapper->SetInputConnection(planeSource->GetOutputPort());

	vtkSmartPointer<vtkActor> planeSourceActor =
		vtkSmartPointer<vtkActor>::New();
	planeSourceActor->SetMapper(planeSourceMapper);

	renderer->GetViewProps()->RemoveAllItems();
	if (background)
		renderer->AddActor(actor3D);
	renderer->AddActor(cutterActor);
	renderer->SetBackground(.1, .2, .3);

	qW->GetRenderWindow()->AddRenderer(renderer);
	qW->GetRenderWindow()->Render();
}

void viewerWidget::addAxes(vtkSmartPointer<vtkPolyData> polydata) {
	axes = true;
	cubeAxesActor =
		vtkSmartPointer<vtkCubeAxesActor>::New();
	cubeAxesActor->SetUseTextActor3D(1);
	cubeAxesActor->SetBounds(bounds);
	cubeAxesActor->SetCamera(renderer->GetActiveCamera());
	cubeAxesActor->GetTitleTextProperty(0)->SetColor(1, 1, 1);
	cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(50);
	cubeAxesActor->GetLabelTextProperty(0)->SetColor(1, 1, 1);

	cubeAxesActor->GetTitleTextProperty(1)->SetColor(1, 1, 1);
	cubeAxesActor->GetLabelTextProperty(1)->SetColor(1, 1, 1);

	cubeAxesActor->GetTitleTextProperty(2)->SetColor(1, 1, 1);
	cubeAxesActor->GetLabelTextProperty(2)->SetColor(1, 1, 1);

	cubeAxesActor->DrawXGridlinesOn();
	cubeAxesActor->DrawYGridlinesOn();
	cubeAxesActor->DrawZGridlinesOn();
	cubeAxesActor->SetGridLineLocation(
		cubeAxesActor->VTK_GRID_LINES_FURTHEST);

	cubeAxesActor->XAxisMinorTickVisibilityOff();
	cubeAxesActor->YAxisMinorTickVisibilityOff();
	cubeAxesActor->ZAxisMinorTickVisibilityOff();

	cubeAxesActor->SetFlyModeToStaticEdges();
	renderer->AddActor(cubeAxesActor);
	renderWindow->Render();
}

void viewerWidget::removeAxes() {
	axes = false;
	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor3D);
	renderer->SetBackground(.1, .2, .3);
	renderWindow->Render();		
}

void viewerWidget::cut1Contour(vtkSmartPointer<vtkPolyData> polydata, double zValue, bool onOgdata) {
	qW->SetRenderWindow(renderWindow);

	polydata->GetBounds(bounds);
	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin(0, 0, 0);
	plane->SetNormal(0, 0, 1);

	vtkSmartPointer<vtkCutter> cutter =
		vtkSmartPointer<vtkCutter>::New();
	cutter->SetInputData(polydata);
	cutter->SetCutFunction(plane);
	cutter->SetValue(0, zValue);

	vtkSmartPointer<vtkPolyDataMapper> cutterMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	cutterMapper->SetInputConnection(cutter->GetOutputPort());
	cutterMapper->ScalarVisibilityOff();
	
	cutterActor->SetPosition(0, 0, 0);
	cutterActor->GetProperty()->SetLineWidth(2);
	cutterActor->SetMapper(cutterMapper);
	cutterActor->GetProperty()->SetColor(1, 0, 0);

	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor3D);
	renderer->AddActor(cutterActor);
	renderer->SetBackground(.1, .2, .3);

	qW->GetRenderWindow()->AddRenderer(renderer);
	qW->GetRenderWindow()->Render();
}

void viewerWidget::optContourOnID(double zValue) {
	renderer->GetViewProps()->RemoveAllItems();
	cutterActor->GetProperty()->SetLineWidth(5);
	cutterActor->SetPosition(0, 0, abs(zValue));
	renderer->AddActor(actor2D);
	renderer->AddActor(cutterActor);
	renderer->SetBackground(1, 1, 1);
	renderWindow->Render();
	resetCam();
}