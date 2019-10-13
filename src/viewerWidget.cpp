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

	//std::cout << "pocet bodov v vw.cpp" << image->GetNumberOfPoints() << std::endl;
	//vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	qW->SetRenderWindow(renderWindow);

	/*vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	vtkPolyData *polyDataTmp = vtkPolyData::New();
	polyDataTmp = polyData;
	mapper->SetInputData(polyData);

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	// actor->GetProperty()->SetPointSize(10);


	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	renderer->AddActor(actor);
	renderer->SetBackground(1, .5, 1);

	//filename annotation
	QByteArray bname = fName.toLocal8Bit();
	vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation = vtkSmartPointer<vtkCornerAnnotation>::New();
	cornerAnnotation->SetLinearFontScaleFactor(2);
	cornerAnnotation->SetNonlinearFontScaleFactor(1);
	cornerAnnotation->SetMaximumFontSize(20);
	//cornerAnnotation->SetText(0, "lower left");
	//cornerAnnotation->SetText(1, "lower right");
	cornerAnnotation->SetText(2, bname.data());
	//cornerAnnotation->SetText(3, "upper right");
	cornerAnnotation->GetTextProperty()->SetColor(0, 0, 0);
	renderer->AddViewProp(cornerAnnotation);*/

	vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
	imageSliceMapper->SetInputData(image);
	imageSliceMapper->BorderOn(); // This line tells the mapper to draw the full border pixels.
	vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
	imageSlice->SetMapper(imageSliceMapper);
	imageSlice->GetProperty()->SetInterpolationTypeToNearest();

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddViewProp(imageSlice);
	renderer->ResetCamera();

// 	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//	renderWindow->AddRenderer(renderer);

//	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();

//	vtkSmartPointer<vtkInteractorStyleImage> style =
//		vtkSmartPointer<vtkInteractorStyleImage>::New();

//	renderWindowInteractor->SetInteractorStyle(style);

	// VTK/Qt wedded
	qW->GetRenderWindow()->AddRenderer(renderer);
}