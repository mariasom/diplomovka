#include "bioData.h"

// Constructor
bioData::bioData(QWidget *parent)
{
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	this->ui->actionAdvanced->setChecked(true);
	advanced = true;
	this->ui->actionAdvanced->setDisabled(true);

	//PushButton = new QPushButton;
	//PushButton1 = new QPushButton;
	//dataUp = new QPushButton;
	//dataDown = new QPushButton;
	otsuButton = new QPushButton;
	kapuraButton = new QPushButton;
	dataListView = new QListWidget;

	innerTabs = new QTabWidget();
	QGridLayout* gridLayout1 = new QGridLayout;
	QGridLayout* gridLayout2 = new QGridLayout;
	//innerTabs->setWidgetResizable();

	//gridLayout1->addWidget(PushButton, 1, 1);
	//gridLayout2->addWidget(PushButton1, 1, 1);

	QScrollArea* VerticalScrollArea = new QScrollArea;
	VerticalScrollArea->setWidgetResizable(true);
	QWidget* contentWidget = new QWidget;
	VerticalScrollArea->setWidget(contentWidget);
	QGridLayout* gridScrollArea = new QGridLayout(contentWidget);
	VerticalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	auto innertabWidget1 = new QWidget;
	innertabWidget1->setLayout(gridLayout1);
	innerTabs->addTab(innertabWidget1, "Basic");
	auto innertabWidget2 = new QWidget;
	innertabWidget2->setLayout(gridLayout2);
	innerTabs->addTab(innertabWidget2, "Advanced");

	//connect(this->PushButton, SIGNAL(clicked()), this, SLOT(pbClicked()));
	//connect(this->PushButton1, SIGNAL(clicked()), this, SLOT(pb1Clicked()));
	connect(this->otsuButton, SIGNAL(clicked()), this, SLOT(otsuClicked()));
	connect(this->kapuraButton, SIGNAL(clicked()), this, SLOT(kapuraClicked()));
	//connect(this->dataUp, SIGNAL(clicked()), this, SLOT(dataUpClicked()));
	//connect(this->dataDown, SIGNAL(clicked()), this, SLOT(dataDownClicked()));
	connect(this->dataListView, SIGNAL(currentRowChanged(int)), this, SLOT(listIndexChanged(int)));


	// plocha pre taby
	//_tabs = new QTabWidget();
	//static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(_tabs, 0, 0);
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

void bioData::keyUpEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Up)
	{
		QMessageBox mbox;
		mbox.setText("key up stlaceny!");
		mbox.exec();
	}
}

void bioData::keyDownEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Down)
	{
		QMessageBox mbox;
		mbox.setText("key down stlaceny!");
		mbox.exec();
	}
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
	reslice->SetInputData(fTmp->getImageData());
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
	filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Portable Graymap (*.pgm)"));
	
	if (filePath.isEmpty()) {
		return;
	}

	fTmp = new source;
	fTmp->load(filePath);
	fTmp->setPoints(fTmp->getOrigData());
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
	scrollArea->setWidgetResizable(true);
	scrollArea->installEventFilter(this);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	//vytvorenie vnutornych layoutov 
	QHBoxLayout* hLayout = new QHBoxLayout;
	QVBoxLayout* vLayout = new QVBoxLayout;

	// vytvorenie GroupBoxov na skalovanie a farbenie, pridanie do vLayoutu
	// createScaleGroupBox();
	// createColorGroupBox();
	//vLayout->addWidget(colorGroupBox);
	// vLayout->addWidget(scaleGroupBox);

	//naplnenie horiz. Layoutu
	//hLayout->addWidget(w->getScrollArea());
	//hLayout->addItem(vLayout);

	//auto tabWidget = new QWidget;
	createFileGroupBox(fName, filePath, fTmp->getWidth(), fTmp->getHeight());
	static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(w->getScrollArea(),0,1);
	
	static_cast<QGridLayout*>(ui->centralwidget->layout())->addWidget(innerTabs,0,0);

	setTabWidget();
	createListGroupBox();
	createFilterGB();

	innerTabs->setCurrentIndex(0);
	static_cast<QGridLayout*>(innerTabs->currentWidget()->layout())->addWidget(fileGroupBox, 0, 0, 1, 1);
	static_cast<QGridLayout*>(innerTabs->currentWidget()->layout())->addWidget(listGroupBox, 1, 0, 1, 1);
	static_cast<QGridLayout*>(innerTabs->currentWidget()->layout())->addWidget(filterGB, 2, 0, 1, 1);
	this->ui->actionAdvanced->setDisabled(false);

	QString dataName = "Original Data";
	dataListView->addItem(dataName);

	// pridanie prazdneho tabu do ktoreho vlozime naplneny widget s horiz. layoutom
	//_tabs->addTab(tabWidget, list[list.length() - 1].left(6));
	// _index++;

	//prepojenie funkcii a pushButtonmi
	//connect(this->scalePushButton, SIGNAL(clicked()), this, SLOT(scaleClicked()));
	//connect(this->colorPushButton, SIGNAL(clicked()), this, SLOT(colorClicked()));

	//fTmp->scale(scaleSpinBox_z->value());
	w->setViewerWidget(fTmp->getImageData(), fTmp->getFileName(fName));
	//visualize();
}

void bioData::setTabWidget() {

	auto tabWidget = new QWidget;

}

// save pgm file
void bioData::actionpgm() {
	int i = dataListView->currentRow();
	QString fileName1 = dataListView->item(i)->text() + ".pgm";
	fTmp->save_ascii(fileName1, i);
}

/*void bioData::pbClicked() {
	QMessageBox mbox;
	mbox.setText("pb kliknuty");
	mbox.exec();
}

void bioData::pb1Clicked() {
	QMessageBox mbox;
	mbox.setText("pb1 kliknuty");
	mbox.exec();
}*/

void bioData::createFileGroupBox(QString name, QString path, int width, int height) {

	fileGroupBox = new QGroupBox(tr("File info"));
	int size = 60;

	QLabel *fileName = new QLabel(tr("File name"));
	QLineEdit *fileName1 = new QLineEdit;
	fileName1->setText(fTmp->getFileName(filePath));
	fileName1->setReadOnly(true);
	fileName1->setCursorPosition(0);
	fileName1->setFrame(QFrame::Panel | QFrame::Sunken);
	QLabel *filePathL = new QLabel(tr("Path"));
	QLineEdit *filePath1 = new QLineEdit;
	filePath1->setText(filePath);
	filePath1->setReadOnly(true);
	filePath1->setCursorPosition(0);
	filePath1->setFrame(QFrame::WinPanel | QFrame::Sunken);

	QLabel *fileWidth = new QLabel(tr("Width"));
	QLineEdit *fileWidth1 = new QLineEdit;
	fileWidth1->setText(QString::number(fTmp->getWidth()));
	fileWidth1->setReadOnly(true);
	fileWidth1->setFrame(QFrame::Panel | QFrame::Sunken);
	fileWidth1->setFixedWidth(size);
	QLabel *fileHeight = new QLabel(tr("Height"));
	QLineEdit *fileHeight1 = new QLineEdit;
	fileHeight1->setText(QString::number(fTmp->getHeight()));
	fileHeight1->setReadOnly(true);
	fileHeight1->setFrame(QFrame::WinPanel | QFrame::Sunken);
	fileHeight1->setFixedWidth(size);

	QSpacerItem *spacer = new QSpacerItem(5, 10);
	QGridLayout *fileLayout = new QGridLayout;
	fileLayout->addWidget(fileName, 0, 0);
	fileLayout->addWidget(fileName1, 0, 1, 1, 4);
	fileLayout->addWidget(filePathL, 1, 0);
	fileLayout->addWidget(filePath1, 1, 1, 1, 4);

	fileLayout->addWidget(fileWidth, 2, 0);
	fileLayout->addWidget(fileWidth1, 2, 1);
	fileLayout->addItem(spacer, 2, 2, 4, 1);
	fileLayout->addWidget(fileHeight, 2, 3);
	fileLayout->addWidget(fileHeight1, 2, 4);

	fileGroupBox->setLayout(fileLayout);
}

void bioData::actionAdvanced() {

	QMessageBox mbox;
	
	if (filePath.isEmpty()) {
	//if (!(this->ui->actionAdvanced->isEnabled())) {
	return;
	}
	else {
		if (this->ui->actionAdvanced->isChecked()) {
			innerTabs->setTabEnabled(1, true);
		}
		else if (!(this->ui->actionAdvanced->isChecked())) {
			innerTabs->setTabEnabled(1,false);
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::createListGroupBox()
{
	listGroupBox = new QGroupBox(tr("Data"));

	//QLabel *Label = new QLabel(tr("Save all steps of filtration"));
	//QString setpath = ()QDir::current();
	//std::cout << ((QString)setpath).toStdString() << std::endl;
	//setpath.cdUp();
	//std::cout << ((QString)(setpath.cdUp())).toStdString() << std::endl;

	//QDir::setSearchPaths("mckps", QStringList(QDir::currentPath() + "/mockups"));
	//dataDown->setIcon(QIcon("mckps:arrow_down.png"));
	//dataDown->setIconSize(QSize(65, 65));
	//dataUp->setIcon(QIcon("mckps:arrow_up.png"));
	
	//dataUp->setText("up");
	//dataUp->setIconSize(QSize(10, 10));
	//dataDown->setText("down");
	//dataDown->setIconSize(QSize(10, 10));
	/*viewCurrentPushButton->setText("OPEN IN NEW TAB");;
	listDeletePushButton->setText("DELETE");;
	listSavePushButton->setText("SAVE");
	listSaveComboBox->addItem("Save selected");
	listSaveComboBox->addItem("Save all");
	listDeleteComboBox->addItem("Delete selected");
	listDeleteComboBox->addItem("Delete all");*/

	QGridLayout *listLayout = new QGridLayout;
	QVBoxLayout* vLayout = new QVBoxLayout;
	listLayout->addWidget(dataListView, 0, 0, 2, 1);
	std::cout << (qApp->applicationDirPath()).toStdString() << endl;
	//listLayout->addWidget(dataUp,0,1,1,1);
	//listLayout->addWidget(dataDown, 1, 1,1,2);
	/*listLayout->addWidget(viewCurrentPushButton, 1, 1);
	listLayout->addWidget(Label, 2, 0);
	listLayout->addWidget(saveCheckbox, 2, 1);
	listLayout->addWidget(listSaveComboBox, 3, 0);
	listLayout->addWidget(listSavePushButton, 3, 1);
	listLayout->addWidget(listDeleteComboBox, 4, 0);
	listLayout->addWidget(listDeletePushButton, 4, 1);*/

	listGroupBox->setLayout(listLayout);
}

void bioData::createFilterGB() {
	filterGB = new QGroupBox(tr("Filters"));

	QGridLayout *filterLayout = new QGridLayout;
	QLabel *otsuLabel = new QLabel(tr("Between-class variance:"));
	QLabel *kapurLabel = new QLabel(tr("Maximum entropy thresholding:"));

	otsuButton->setText("Apply");
	filterLayout->addWidget(otsuLabel,0,0);
	filterLayout->addWidget(otsuButton, 0, 1);
	kapuraButton->setText("Apply");
	filterLayout->addWidget(kapurLabel, 1, 0);
	filterLayout->addWidget(kapuraButton, 1, 1);

	filterGB->setLayout(filterLayout);
}

void bioData::otsuClicked() {

	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());
	filter.histogram();
	filter.otsuFilter();
	fTmp->addFiltData(filter.getFiltDat());

	QString item = "otsu";
	dataListView->addItem(item);
//	dataListView->setCurrentRow(dataListView->count() - 1);
	std::cout << "size of filt data: " << fTmp->getSizeFiltData() << std::endl;
	fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData()-1));
	w->updateViewerWidget();
}

void bioData::kapuraClicked() {

	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());
	filter.histogram();
	filter.kapuraFilter();
	fTmp->addFiltData(filter.getFiltDat());

	QString item = "kapura";
	dataListView->addItem(item);
	//	dataListView->setCurrentRow(dataListView->count() - 1);
	std::cout << "size of filt data: " << fTmp->getSizeFiltData() << std::endl;
	fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
	w->updateViewerWidget();
}

void bioData::listIndexChanged(int i)
{
	if (i == -1)
		return;
	else {
		fTmp->setPoints(fTmp->getFiltData(i));
		w->updateViewerWidget();
	}
}

