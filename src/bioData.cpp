#include "bioData.h"

// Constructor
bioData::bioData() {
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	// plocha pre taby
	_tabs = new QTabWidget();
	static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(_tabs, 0, 0);

	// Set up action signals and slots
	// connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

/*bioData::bioData() {
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	QFont f("Times New Roman", 10, QFont::Normal);

	QScrollArea* VerticalScrollArea = new QScrollArea;
	VerticalScrollArea->setWidgetResizable(true);
	QWidget* contentWidget = new QWidget;
	VerticalScrollArea->setWidget(contentWidget);
	QGridLayout* gridScrollArea = new QGridLayout(contentWidget);
	VerticalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}*/

void bioData::slotExit()
{
	qApp->exit();
}

bool bioData::eventFilter(QObject * obj, QEvent * event)
{
	if (obj->objectName() == "QScrollArea") {
		QScrollAreaEventFilter(obj, event);
	}

	return false;
}

bool bioData::QScrollAreaEventFilter(QObject * obj, QEvent * event)
{
	QScrollArea* s = static_cast<QScrollArea*>(obj);
	if (event->type() == QEvent::Resize) {
		if (s->widget()) {
			viewerWidget* w = static_cast<viewerWidget*>(s->widget());
			w->setAreaSize(s->size());
		}
	}
	else {
		// standard event processing
		return QObject::eventFilter(obj, event);
	}

	return false;
}

void bioData::visualize()
{


	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	// qW->SetRenderWindow(renderWindow);
	w->getQVTKwidget()->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
	imageSliceMapper->SetInputData(fTmp->getData());
	imageSliceMapper->BorderOn(); // This line tells the mapper to draw the full border pixels.
	vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
	imageSlice->SetMapper(imageSliceMapper);
	imageSlice->GetProperty()->SetInterpolationTypeToNearest();

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddViewProp(imageSlice);
	renderer->ResetCamera();

	// qW->GetRenderWindow()->AddRenderer(renderer);
	w->getQVTKwidget()->GetRenderWindow()->AddRenderer(renderer);

	// metoda, ktora obsluzi vsetko co sa tyka kreslenia na plochu
	/*vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	w->getQVTKwidget()->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(fTmp->getPolyData(colorComboBox->currentIndex()));

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();

	renderer->AddActor(actor);
	renderer->SetBackground(1, 1, 1);

	//filename annotation
	QByteArray bname = fName.toLocal8Bit();
	vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation =
		vtkSmartPointer<vtkCornerAnnotation>::New();
	cornerAnnotation->SetLinearFontScaleFactor(2);
	cornerAnnotation->SetNonlinearFontScaleFactor(1);
	cornerAnnotation->SetMaximumFontSize(20);
	//cornerAnnotation->SetText(0, "lower left");
	//cornerAnnotation->SetText(1, "lower right");
	cornerAnnotation->SetText(2,bname.data());
	//cornerAnnotation->SetText(3, "upper right");
	cornerAnnotation->GetTextProperty()->SetColor(0, 0, 0);
	renderer->AddViewProp(cornerAnnotation);

	// VTK/Qt wedded
	w->getQVTKwidget()->GetRenderWindow()->AddRenderer(renderer);*/
}

void bioData::actionOpenFile()
{
	// nacitanie suboru
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Portable Graymap (*.pgm)"));
	if (filePath.isEmpty()) {
		return;
	}

	fTmp = new source;
	fTmp->load(filePath);
	fTmp->setPoints();
	// extrahovanie nazvu suboru s cesty
	QStringList list = filePath.split('/');
	fName = list[list.length() - 1];

	//vytvorenie viewer widgetu
	w = new viewerWidget();
	//w->setViewerWidget(fTmp->getPolyData(colorComboBox->currentIndex()), fName);
	w->setScrollArea();

	//w = new viewerWidget();
	//vytvorenie scroll area a pridanie Widgetu
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setObjectName("QScrollArea");
	scrollArea->setWidget(w);
	scrollArea->setBackgroundRole(QPalette::Light);
	scrollArea->setWidgetResizable(false);
	scrollArea->installEventFilter(this);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//vytvorenie vnutornych layoutov 
	QHBoxLayout* hLayout = new QHBoxLayout;
	QVBoxLayout* vLayout = new QVBoxLayout;

	// vytvorenie GroupBoxov na skalovanie a farbenie, pridanie do vLayoutu
	// createScaleGroupBox();
	// createColorGroupBox();
	// vLayout->addWidget(colorGroupBox);
	// vLayout->addWidget(scaleGroupBox);

	//naplnenie horiz. Layoutu
	hLayout->addWidget(w->getScrollArea());
	hLayout->addItem(vLayout);

	auto tabWidget = new QWidget;
	tabWidget->setLayout(hLayout);
	// pridanie prazdneho tabu do ktoreho vlozime naplneny widget s horiz. layoutom
	_tabs->addTab(tabWidget, list[list.length() - 1].left(6));
	// _index++;

	//prepojenie funkcii a pushButtonmi
	//connect(this->scalePushButton, SIGNAL(clicked()), this, SLOT(scaleClicked()));
	//connect(this->colorPushButton, SIGNAL(clicked()), this, SLOT(colorClicked()));

	//fTmp->scale(scaleSpinBox_z->value());
	std::cout << "data v biodata.cpp" << fTmp->getData()->GetNumberOfPoints() << std::endl;
	// w->setViewerWidget(fTmp->getData(), fTmp->getFileName(fName));
	visualize();
}

void bioData::actionClose()
{
	// vymaze aktualny tab			DOROBIT: dealokaciu seckiho co bolo v tom tabe
	if (_index >= 0)
	{
		_index = _tabs->currentIndex();
		_tabs->removeTab(_index);
	}
}
