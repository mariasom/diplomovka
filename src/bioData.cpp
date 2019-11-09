#include "bioData.h"

// Constructor
bioData::bioData() {
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	// plocha pre taby
	//_tabs = new QTabWidget();
	static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(_tabs, 0, 0);
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

void bioData::slotExit()
{
	qApp->exit();
}

void bioData::actionClose()
{
	qApp->exit();
}

void bioData::visualize()
{
	/*vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	// qW->SetRenderWindow(renderWindow);
	w->getQVTKwidget()->SetRenderWindow(renderWindow);

	std::cout << fTmp->getData()->GetCellData() << std::endl;
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(fTmp->getData());
	std::cout << "data v biodata.cpp" << fTmp->getData()->GetNumberOfPoints() << std::endl;

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->GetProperty()->SetPointSize(10);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	
	renderWindow->AddRenderer(renderer);
	renderer->AddActor(actor);
	renderer->SetBackground(1, 0, 1);
	renderer->ResetCamera();

	w->getQVTKwidget()->GetRenderWindow()->AddRenderer(renderer);*/

	vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
	// qW->SetRenderWindow(renderWindow);
	w->getQVTKwidget()->SetRenderWindow(renderWindow);

	vtkSmartPointer<vtkImageReslice> reslice = vtkSmartPointer<vtkImageReslice>::New();
	reslice->SetInputData(fTmp->getData());
	//reslice->SetOutputSpacing(0);
	reslice->SetInterpolate(0);
	reslice->Update();
	//std::cout << reslice->GetInformation();
	//

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

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindow->Render();
	renderWindowInteractor->Start();

	/*vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindow->Render();
	renderWindowInteractor->Start();*/
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
	w->setViewerWidget(fTmp->getData(), fTmp->getFileName(fName));
	//visualize();
}

// save pgm file
void bioData::actionpgm() {
	
	
}

void bioData::actionAdvanced() {

}