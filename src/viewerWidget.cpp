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
	renderer3D->SetBackground(0,0,0);
	renderWindow3D->Render();
}

void viewerWidget::setViewerWidget3D(vtkSmartPointer<vtkPolyData> polydata) {
	qW3D->SetRenderWindow(renderWindow3D);
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->ScalarVisibilityOff();
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

void viewerWidget::contours3D(vtkSmartPointer<vtkPolyData> polydata, int numOfCont) {
	qW3D->SetRenderWindow(renderWindow3D);

	double bounds[6];
	polydata->GetBounds(bounds);
	std::cout << "xmin: " << bounds[0] << " "
		<< "xmax: " << bounds[1] << std::endl
		<< "ymin: " << bounds[2] << " "
		<< "ymax: " << bounds[3] << std::endl
		<< "zmin: " << bounds[4] << " "
		<< "zmax: " << bounds[5] << std::endl;
	vtkSmartPointer<vtkContourFilter> contour = vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputData(polydata);

	// contour->SetNumberOfContours(10);
	contour->ComputeNormalsOn();
	//for (int i = 0; i < 18; i++) {
	// contour->SetValue(0, 255);
	//}
	double getRange = abs(bounds[5] - bounds[4]);
	std:cout << getRange << endl;
	contour->GenerateValues(20,0, getRange*10);
	contour->GetUseScalarTree();
	vtkSmartPointer<vtkPolyDataMapper> contourMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contour->GetOutputPort());
	// contourMapper->ScalarVisibilityOff();
	contourMapper->SetScalarRange(polydata->GetScalarRange());

	vtkSmartPointer<vtkActor> contourActor = vtkSmartPointer<vtkActor>::New();
	contourActor->GetProperty()->SetLineWidth(2);
	contourActor->SetMapper(contourMapper);

	renderer3D->GetViewProps()->RemoveAllItems();
	renderer3D->AddActor(contourActor);
	renderer3D->SetBackground(.1, .2, .3);

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);

}

void viewerWidget::setViewerWidget(vtkSmartPointer<vtkImageData> image) {
	// 2D contour
	qW2D->SetRenderWindow(renderWindow2D);

	vtkSmartPointer<vtkNamedColors> colors =
		vtkSmartPointer<vtkNamedColors>::New();

	vtkSmartPointer<vtkContourFilter> contourFilter =
		vtkSmartPointer<vtkContourFilter>::New();
	contourFilter->SetInputData(image);
	contourFilter->GenerateValues(1, 10, 10); // (numContours, rangeStart, rangeEnd)

	// Map the contours to graphical primitives
	vtkSmartPointer<vtkPolyDataMapper> contourMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contourFilter->GetOutputPort());

	// Create an actor for the contours
	vtkSmartPointer<vtkActor> contourActor =
		vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);
	contourActor->GetProperty()->SetLineWidth(5);

	// Create the outline
	vtkSmartPointer<vtkOutlineFilter> outlineFilter =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outlineFilter->SetInputData(image);

	vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());
	vtkSmartPointer<vtkActor> outlineActor =
		vtkSmartPointer<vtkActor>::New();
	outlineActor->SetMapper(outlineMapper);
	outlineActor->GetProperty()->SetColor(0, .5, 0);
	outlineActor->GetProperty()->SetLineWidth(3);

	vtkSmartPointer<vtkTexture> texture =
		vtkSmartPointer<vtkTexture>::New();
	texture->SetInputData(image);

	// Visualize

	renderer2D->GetViewProps()->RemoveAllItems();
	renderer2D->AddActor(contourActor);
	renderer2D->AddActor(outlineActor);
	renderer2D->SetBackgroundTexture(texture);
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
		QMessageBox mbox;
		mbox.setText("here i am");
		mbox.exec();
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