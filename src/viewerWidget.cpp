#include "viewerWidget.h"

viewerWidget::viewerWidget(QWidget *parent) : QWidget(parent)
{
	setAttribute(Qt::WA_StaticContents);
	qW = new QVTKOpenGLNativeWidget(this);

	hue_Lut = vtkSmartPointer<vtkLookupTable>::New();
	scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
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

void viewerWidget::setViewerWidget(vtkSmartPointer<vtkPolyData> polyData, QString fName)
{
	qW->SetRenderWindow(renderWindow);

	mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polyData);
	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor);
	renderer->AddActor(scalarBar);
	renderer->SetBackground(1, 1, 1);
//	renderer->AddViewProp(cornerAnnotation(fName));

	// VTK/Qt wedded
	qW->GetRenderWindow()->AddRenderer(renderer);
}

/*void viewerWidget::updateViewerWidget(vtkSmartPointer<vtkPolyData> polyData, QString fName, QString filterInfo, bool scale)
{
	// updatne vykreslovaciu plochu
	mapper->SetInputData(polyData);
	mapper->Update();

	actor->SetMapper(mapper);

	if (!filterInfo.isEmpty() || !fName.isEmpty())
		renderer->GetViewProps()->RemoveAllItems();
	renderer->AddActor(actor);
	renderer->AddActor(scalarBar);

	if (scale)
		renderer->ResetCamera();

	renderWindow->Render();
}

void viewerWidget::resetCamera(int width, int height)
{
	renderer->GetActiveCamera()->SetPosition(width / 2.0, height / 2.0, (width + height)*2.5);
	renderer->GetActiveCamera()->SetViewUp(0, 1, 0);

	renderer->ResetCamera();
	renderWindow->Render();
}

vtkSmartPointer<vtkScalarBarActor> viewerWidget::setScalarBar(vtkSmartPointer<vtkScalarBarActor> scalbar)
{
	scalarBar = scalbar;
	return scalarBar;
}*/
