#include "viewerWidget.h"

viewerWidget::viewerWidget(QWidget *parent) : QWidget(parent) {
	setAttribute(Qt::WA_StaticContents);
	qW2D = new QVTKOpenGLNativeWidget(this);
	qW3D = new QVTKOpenGLNativeWidget(this);
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

void viewerWidget::setViewerWidget2D(vtkSmartPointer<vtkImageData> image, QString fName) {
	//vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	qW2D->SetRenderWindow(renderWindow2D);

	vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	//imageStyle->SetInteractionMode(1);
	imageStyle->SetInteractionModeToImage2D();
	//imageStyle->StartRotate();
	//std::cout << imageStyle->GetInteractionMode() << std::endl;
	qW2D->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);

	//vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
	//reslice->SetInputData(image);
	//reslice->SetOutputSpacing(0);
	//reslice->SetInterpolate(0);
	//reslice->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	//mapper->InterpolateScalarsBeforeMappingOn();
	//mapper->SetInputData(reslice->GetOutput());
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

	qW3D->GetRenderWindow()->AddRenderer(renderer3D);
}
