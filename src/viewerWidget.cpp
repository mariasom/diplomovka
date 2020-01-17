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

void viewerWidget::setViewerWidget(vtkSmartPointer<vtkImageData> image, QString fName)
{
	//vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	qW->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	//imageStyle->SetInteractionMode(1);
	imageStyle->SetInteractionModeToImage2D();
	//imageStyle->StartRotate();
	//std::cout << imageStyle->GetInteractionMode() << std::endl;
	qW->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);

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

	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();

	renderWindow->AddRenderer(renderer);
	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);
	renderer->ResetCamera();

	qW->GetRenderWindow()->AddRenderer(renderer);
}

void viewerWidget::updateViewerWidget()
{
	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);

	renderWindow->Render();
}

void viewerWidget::updateViewerWidget(vtkSmartPointer<vtkPolyData> polydata)
{
	vtkSmartPointer<vtkPolyDataMapper> mapper1 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper1->SetInputData(polydata);

	vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
	actor1->SetMapper(mapper1);
	//actor1->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
	//actor1->GetProperty()->SetPointSize(10);

	vtkSmartPointer<vtkRenderer> renderer1 =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow1 =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow1->AddRenderer(renderer1);

	// An interactor
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow1);

	//renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer1->GetViewProps()->RemoveAllItems();
	renderer1->AddActor(actor1);
	//renderer->AddActor(scalarBar);
	renderer1->SetBackground(.1, .2, .3);
	//renderer->AddViewProp(cornerAnnotation(fName));

	//renderWindow1->Render();
	renderWindowInteractor->Start();
}

