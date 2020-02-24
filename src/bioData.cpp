#include "bioData.h"

// Constructor
bioData::bioData(QWidget *parent)
{
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	this->ui->actionAdvanced->setChecked(true);
	this->ui->actionAll->setChecked(true);
	this->ui->actionFileInfo->setChecked(true);
	this->ui->actionData->setChecked(true);
	this->ui->actionFilters->setChecked(true);
	advanced = true;
	this->ui->actionAdvanced->setDisabled(true);
	this->ui->menuTabs->setDisabled(true);

	//dataUp = new QPushButton;
	//dataDown = new QPushButton;
	otsuButton = new QPushButton;
	kapuraButton = new QPushButton;
	niblackButton = new QPushButton;
	boundaryButton = new QPushButton;
	//dataListView = new QListWidget;
	dataTree = new QTreeWidget;
	useOData = new QCheckBox;
	originalCol = new QCheckBox;
	foregroundSB = new QSpinBox;
	backgroundSB = new QSpinBox;

	originalCol->setChecked(true);
	originalCol->setDisabled(true);
	useOData->setChecked(true);
	useOData->setDisabled(true);

	innerTabs = new QTabWidget();
	QGridLayout* gridLayout1 = new QGridLayout;
	QGridLayout* gridLayout2 = new QGridLayout;
	//innerTabs->setWidgetResizable();

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

	connect(this->otsuButton, SIGNAL(clicked()), this, SLOT(otsuClicked()));
	connect(this->kapuraButton, SIGNAL(clicked()), this, SLOT(kapuraClicked()));
	connect(this->niblackButton, SIGNAL(clicked()), this, SLOT(niblackClicked()));
	connect(this->boundaryButton, SIGNAL(clicked()), this, SLOT(boundaryClicked()));
	//connect(this->dataUp, SIGNAL(clicked()), this, SLOT(dataUpClicked()));
	//connect(this->dataDown, SIGNAL(clicked()), this, SLOT(dataDownClicked()));
	//connect(this->dataListView, SIGNAL(currentRowChanged(int)), this, SLOT(listIndexChanged(int)));
	//connect(this->dataTree, SIGNAL(currentItemChanged(QTreeWidgetItem, QTreeWidgetItem)), this, SLOT(treeIndexChanged(QTreeWidgetItem, QTreeWidgetItem)));
	connect(this->dataTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(treeIndexChanged(QTreeWidgetItem *, int)));

	// space for the display area
	mdiArea = new QMdiArea(this); 
	// configure scrollbars
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	// Set Mdi Area as the central widget
	setCentralWidget(mdiArea);
}

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
			//tu je nejaky odzub premysliet co ak ma 3D area inu velkost?
			viewerWidget* w = static_cast<viewerWidget*>(s->widget());
			w->setAreaSize2D(s->size());
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

void bioData::actionOpenFile()
{
	// file load
	filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Portable Graymap (*.pgm)"));
	
	if (filePath.isEmpty()) {
		return;
	}

	fTmp = new source;
	fTmp->load(filePath);
	fTmp->setPoints(fTmp->getOrigData());
	// extract filename from the path
	QStringList list = filePath.split('/');
	fName = list[list.length() - 1];

	w = new viewerWidget();

	createFileDock(fName, filePath, fTmp->getWidth(), fTmp->getHeight());
	createListDock();
	createFilterDock();
	this->ui->menuTabs->setDisabled(false);

	if (widget2D == nullptr)
		set2DWidget();
	else
		update2DWidget();
	widget2D->setWindowTitle("Original Data");
	addSubItem(parent2D, "Original Data");
	// QString dataName = "Original Data";
	// dataListView->addItem(dataName);
	// dataListView->setCurrentRow(dataListView->count() - 1);
}

void bioData::addSubItem(QTreeWidgetItem *parent, QString name) {
	QTreeWidgetItem *itm = new QTreeWidgetItem();
	itm->setText(0, name);
	parent->addChild(itm);
	dataTree->setCurrentItem(itm);
}

void bioData::setTabWidget() {
	auto tabWidget = new QWidget;
}

// save pgm file
void bioData::actionpgm() {
	int i = dataTree->currentItem()->indexOfChild(dataTree->currentItem());
	QString fileName1 = dataTree->currentItem()->text(0) + ".pgm";
	fTmp->save_ascii(fileName1, i);
}

void bioData::createFileDock(QString name, QString path, int width, int height) {

	fileDock = new QDockWidget(tr("File Info"), this);
	fileDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	fileDock->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetVerticalTitleBar);
	int size = 60;

	QLabel *fileName = new QLabel(tr("File name"));
	QLineEdit *fileName1 = new QLineEdit;
	fileName1->setText(name);
	fileName1->setReadOnly(true);
	fileName1->setCursorPosition(0);
	fileName1->setFrame(QFrame::Panel | QFrame::Sunken);
	QLabel *filePathL = new QLabel(tr("Path"));
	QLineEdit *filePath1 = new QLineEdit;
	filePath1->setText(path);
	filePath1->setReadOnly(true);
	filePath1->setCursorPosition(0);
	filePath1->setFrame(QFrame::WinPanel | QFrame::Sunken);

	QLabel *fileWidth = new QLabel(tr("Width"));
	QLineEdit *fileWidth1 = new QLineEdit;
	fileWidth1->setText(QString::number(width));
	fileWidth1->setReadOnly(true);
	fileWidth1->setFrame(QFrame::Panel | QFrame::Sunken);
	fileWidth1->setFixedWidth(size);
	QLabel *fileHeight = new QLabel(tr("Height"));
	QLineEdit *fileHeight1 = new QLineEdit;
	fileHeight1->setText(QString::number(height));
	fileHeight1->setReadOnly(true);
	fileHeight1->setFrame(QFrame::WinPanel | QFrame::Sunken);
	fileHeight1->setFixedWidth(size);

	QWidget* multiWidget = new QWidget();
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

	multiWidget->setLayout(fileLayout);
	fileDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, fileDock);
}

void bioData::actionAdvanced() {

	QMessageBox mbox;
	if (filePath.isEmpty()) {
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

void bioData::actionAll() {

	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->actionAll->isChecked()) {
			listDock->show();
			filterDock->show();
			fileDock->show();
		}
		else if (!(this->ui->actionAll->isChecked())) {
			listDock->hide();
			filterDock->hide();
			fileDock->hide();
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::actionFileInfo() {

	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->actionFileInfo->isChecked()) {
			fileDock->show();
		}
		else if (!(this->ui->actionFileInfo->isChecked())) {
			fileDock->hide();
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::actionData() {

	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->actionData->isChecked()) {
			listDock->show();
		}
		else if (!(this->ui->actionData->isChecked())) {
			listDock->hide();
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::actionFilters() {

	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->actionFilters->isChecked()) {
			filterDock->show();
		}
		else if (!(this->ui->actionFilters->isChecked())) {
			filterDock->hide();
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::createListDock() {
	listDock = new QDockWidget(tr("Data"), this);
	listDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	listDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable | 
		QDockWidget::DockWidgetVerticalTitleBar);
	QLabel *Label = new QLabel(tr("Work with original data: "));

	QWidget* multiWidget = new QWidget();
	QGridLayout *listLayout = new QGridLayout;
	QVBoxLayout* vLayout = new QVBoxLayout;
	//listLayout->addWidget(dataListView, 0, 0, 2, 2);
	dataTree->setHeaderHidden(true);
	dataTree->setColumnCount(1);
	listLayout->addWidget(dataTree, 0, 0, 2, 2);
	listLayout->addWidget(Label, 2, 0, 2, 1);
	listLayout->addWidget(useOData, 2, 1, 2, 1);

	multiWidget->setLayout(listLayout);
	listDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, listDock);
}

void bioData::createFilterDock() {
	filterDock = new QDockWidget(tr("Filters"), this);
	filterDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	filterDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);

	QWidget* multiWidget = new QWidget();
	QGridLayout *filterLayout = new QGridLayout;
	QLabel *otsuLabel = new QLabel(tr("Between-class variance:"));
	QLabel *kapurLabel = new QLabel(tr("Maximum entropy thresholding:"));
	QLabel *niblackLabel = new QLabel(tr("Niblack’s original method:"));
	QLabel *boundaryLabel = new QLabel(tr("SUBSURF:"));

	otsuButton->setText("Apply");
	filterLayout->addWidget(otsuLabel,0,0);
	filterLayout->addWidget(otsuButton, 0, 1);
	kapuraButton->setText("Apply");
	filterLayout->addWidget(kapurLabel, 1, 0);
	filterLayout->addWidget(kapuraButton, 1, 1);
	niblackButton->setText("Apply");
	filterLayout->addWidget(niblackLabel, 2, 0);
	filterLayout->addWidget(niblackButton, 2, 1);
	boundaryButton->setText("Apply");
	filterLayout->addWidget(boundaryLabel, 3, 0);
	filterLayout->addWidget(boundaryButton, 3, 1);
	   	 
	multiWidget->setLayout(filterLayout);
	filterDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, filterDock);
}

void bioData::otsuClicked() {

	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());
	fTmp->addFiltData(filter.createNewData(fTmp->getOrigData(), filter.otsuFilter()));
	fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
	if (widget2D == nullptr)
		set2DWidget();
	else
		update2DWidget();
	// Set the window title
	widget2D->setWindowTitle("Otsu Threshold");
	addSubItem(parent2D, "otsu");
	//QString item = "otsu";
	//dataListView->addItem(item);
    //dataListView->setCurrentRow(dataListView->count() - 1);
	//std::cout << "size of filt data: " << fTmp->getSizeFiltData() << std::endl;
	fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
	/*widget2D->setWindowTitle("Otsu Threshold");
	w->updateViewerWidget2D();
	widget2D->update();*/
}

void bioData::kapuraClicked() {

	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());
	//filter.histogram();
	fTmp->addFiltData(filter.createNewData(fTmp->getOrigData(), filter.kapuraFilter()));
	fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
	if (widget2D == nullptr)
		set2DWidget();
	else
		update2DWidget();
	// Set the window title
	widget2D->setWindowTitle("kapur");
	addSubItem(parent2D, "kapur");

	// QString item = "kapur";
	// dataListView->addItem(item);
	// dataListView->setCurrentRow(dataListView->count() - 1);
	// std::cout << "size of filt data: " << fTmp->getSizeFiltData() << std::endl;

	//w->updateViewerWidget2D();
}

void bioData::niblackClicked() {
	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData(),7);
	QVector<unsigned char> tmp = filter.dataToChar(filter.niblackThreshold(filter.changeRangeOfData(filter.dataToInt(fTmp->getOrigData()))));
	fTmp->addFiltData(tmp);
	fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
	if (widget2D == nullptr)
		set2DWidget();
	else
		update2DWidget();
	// Set the window title
	widget2D->setWindowTitle("niblack");
	addSubItem(parent2D, "niblack");
}

void bioData::listIndexChanged(int i)
{
	if (i == -1)
		return;
	else {
		QMessageBox mbox;
		mbox.setText("index changed");
		mbox.exec();
		fTmp->setPoints(fTmp->getFiltData(i));
		w->updateViewerWidget2D();
	}
}

void bioData::treeIndexChanged(QTreeWidgetItem *itm, int i) {
	//if (i == 0) {
		QMessageBox mbox;
		//mbox.setText(QString::number(itm->parent()->indexOfChild(itm)));
		//mbox.exec();
		//mbox.setText(QString::number(i));
		//mbox.exec();
		// itm->parent()->indexOfChild(itm);
		if (itm->parent() == parent2D) {

			fTmp->setPoints(fTmp->getFiltData(dataTree->currentIndex().row()));
			w->updateViewerWidget2D();
			if (widget3D != nullptr)
				widget3D->hide();
			widget2D->show();
		}
		else if (itm->parent() == parent3D) {
			fTmp->create3Ddata(fTmp->get3DData(dataTree->currentIndex().row()));
			w->updateViewerWidget3D();
			if (widget2D != nullptr)
				widget2D->hide();
			widget3D->show();
		}
		//else if (itm->parent()) {
		//	mbox.setText("tu som ");
		//	mbox.exec();
		//}
	//}
}

void bioData::createColorsGB() {
	colorsGB = new QGroupBox(tr("Colors"));

	QGridLayout *colorLayout = new QGridLayout;
	QLabel *backgroundLab = new QLabel(tr("Background: "));
	QLabel *foregroundLab = new QLabel(tr("Foreground: "));
	QLabel *label = new QLabel(tr("Use default color settings: "));

	foregroundSB->setRange(0, 255);
	foregroundSB->setSingleStep(1);
	foregroundSB->setValue(207);
	foregroundSB->setDisabled(true);
	backgroundSB->setRange(0, 255);
	backgroundSB->setSingleStep(1);
	backgroundSB->setValue(0);
	backgroundSB->setDisabled(true);

	colorLayout->addWidget(backgroundLab, 0, 0);
	colorLayout->addWidget(backgroundSB, 0, 1);
	colorLayout->addWidget(foregroundLab, 1, 0);
	colorLayout->addWidget(foregroundSB, 1, 1);
	colorLayout->addWidget(label, 2, 0);
	colorLayout->addWidget(originalCol, 2, 1);

	colorsGB->setLayout(colorLayout);
}

void bioData::boundaryClicked() {
	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());
	QVector<double> tmp = filter.subSurf(
		filter.distFunctSign(
			filter.boundary(filter.dataToDouble(fTmp->getOrigData()), filter.otsuFilter())),
		filter.changeRangeOfData(
			filter.dataToInt(
				filter.niblackThreshold(filter.changeRangeOfData(filter.dataToInt(fTmp->getOrigData()))))));
	//histogram();
	//filter.boundary();
	//filter.subSurf(filter.distFunctSign(fTmp->getFiltData(0)));
	//filter.distFunctSign(filter.dataToDouble(fTmp->getFiltData(0)));
	fTmp->add3DData(tmp);
	fTmp->create3Ddata(fTmp->get3DData(fTmp->getSize3DData() - 1));
	// fTmp->create3Ddata(filter.subSurf(
	//	filter.distFunctSign(
	//		filter.boundary(
	//			filter.dataToInt(fTmp->getOrigData()), filter.otsuFilter())),
	//	filter.changeRangeOfData(
	//		filter.dataToInt(
	//			filter.createNewData(
	//				filter.dataToInt(fTmp->getOrigData()), filter.otsuFilter())))));
	
	if (widget3D == nullptr)
		set3DWidget();
	else
		update3DWidget();
	// Set the window title
	widget3D->setWindowTitle("Subsurf(3D)");
	addSubItem(parent3D, "Subsurf");
//	fTmp->create3Ddata(filter.heatImpl(filter.changeRangeOfData(
//		filter.dataToInt(
//			filter.createNewData(
//				filter.dataToInt(
//					fTmp->getOrigData()), filter.kapuraFilter())))));
//QVector<int> tmp = filter.boundary(filter.dataToInt(fTmp->getOrigData()), filter.otsuFilter());
	//fTmp->addFiltData(filter.dataToChar(filter.subSurf(filter.distFunctSign(filter.boundary(filter.dataToInt(fTmp->getOrigData()), filter.otsuFilter())), 
	//	filter.changeRangeOfData(filter.dataToInt(filter.createNewData(filter.dataToInt(fTmp->getOrigData()), filter.kapuraFilter()))))));

	//QString item = "subSurf";
	//dataListView->addItem(item);
	//dataListView->setCurrentRow(dataListView->count() - 1);
	//std::cout << "size of filt data: " << fTmp->getSizeFiltData() << std::endl;
	//w->set(fTmp->get3Data(), " ");
	//w->updateViewerWidget(fTmp->get3Data());
	//w->updateViewerWidget();
//	w->updateViewerWidget(fTmp->get3Data());
}

void bioData::actionDistFunc() {
	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());	
	QVector<double> tmp = filter.distFunct(filter.boundary(filter.dataToDouble(fTmp->getOrigData()), filter.otsuFilter()));
	fTmp->add3DData(tmp);
	fTmp->create3Ddata(fTmp->get3DData(fTmp->getSize3DData() - 1));

	if (widget3D == nullptr)
		set3DWidget();
	else
		update3DWidget();
	// Set the window title
	widget3D->setWindowTitle("Distanced Function");
	addSubItem(parent3D, "dist_function");
}

void bioData::set3DWidget() {
	widget3D = new QWidget(mdiArea);
	parent3D = new QTreeWidgetItem();
	parent3D->setText(0, "3D");
	dataTree->addTopLevelItem(parent3D);
	w->setScrollArea3D();
	gridLayout3D = new QGridLayout(widget3D); 
	gridLayout3D->addWidget(w->getScrollArea3D());
	w->setViewerWidget3D(fTmp->getPolydata());
	// Adding a widget as a sub window in the Mdi Area
	mdiArea->addSubWindow(widget3D);
	mdiArea->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->setWindowFlags(Qt::WindowTitleHint);
	// And show the widget
	widget3D->show();
	mdiArea->currentSubWindow()->showMaximized();
}

void bioData::update3DWidget() {
	w->updateViewerWidget3D();
	widget3D->update();
	widget3D->show();
}

void bioData::set2DWidget() {
	widget2D = new QWidget(mdiArea); 
	parent2D = new QTreeWidgetItem();
	parent2D->setText(0, "2D");
	dataTree->addTopLevelItem(parent2D);
	w->setScrollArea2D();
	gridLayout2D = new QGridLayout(widget2D);
	gridLayout2D->addWidget(w->getScrollArea2D());
	w->setViewerWidget2D(fTmp->getImageData(), fTmp->getFileName(fName));
	// Adding a widget as a sub window in the Mdi Area
	mdiArea->addSubWindow(widget2D);
	//QString twod = "2D";
	//dataListView->addItem(twod);
	//dataListView->item(0)->setFlags(Qt::ItemIsAutoTristate);
	// And show the widget
	widget2D->show();
	mdiArea->currentSubWindow()->showMaximized();
}

void bioData::update2DWidget() {
	w->updateViewerWidget2D();
	widget2D->update();
	widget2D->show();
}

void bioData::actionSignDistFunc() {
	filters filter(fTmp->getWidth(), fTmp->getHeight(), fTmp->getOrigData());
	//fTmp->create3Ddata(filter.distFunctSign(filter.boundary(filter.dataToInt(fTmp->getOrigData()), filter.otsuFilter())));
	QVector<double> tmp = filter.distFunctSign(filter.boundary(filter.dataToDouble(fTmp->getOrigData()), filter.otsuFilter()));
	fTmp->add3DData(tmp);
	fTmp->create3Ddata(fTmp->get3DData(fTmp->getSize3DData() - 1));

	if (widget3D == nullptr)
		set3DWidget();
	else
		update3DWidget();
	// Set the window title
	widget3D->setWindowTitle("Sign Distanced Function");	
	addSubItem(parent3D, "sign_dist_function");
}

void bioData::createDockWidgets() {
}