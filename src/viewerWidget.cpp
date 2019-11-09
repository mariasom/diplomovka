#include "viewerWidget.h"

viewerWidget::viewerWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	qW = new QVTKOpenGLNativeWidget(this);
}


viewerWidget::~viewerWidget()
{
}

void viewerWidget::setScrollArea()
{
	_scrollArea = new QScrollArea;
	_scrollArea->setObjectName("QScrollArea");
	_scrollArea->setWidget(qW);
	_scrollArea->setBackgroundRole(QPalette::Dark);
	_scrollArea->setWidgetResizable(true);
	_scrollArea->installEventFilter(this);
	_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void viewerWidget::setViewerWidget(vtkSmartPointer<vtkImageData> image, QString fName)
{
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	qW->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
	reslice->SetInputData(image);
	//reslice->SetOutputSpacing(0);
	reslice->SetInterpolate(0);
	reslice->Update();

	vtkSmartPointer<vtkDataSetMapper> mapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
	//mapper->InterpolateScalarsBeforeMappingOn();
	mapper->SetInputData(reslice->GetOutput());

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();

	renderWindow->AddRenderer(renderer);
	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);
	renderer->ResetCamera();

	qW->GetRenderWindow()->AddRenderer(renderer);
}