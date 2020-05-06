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
	this->ui->action2DFilters->setChecked(true);
	this->ui->action3DFilters->setChecked(true);
	this->ui->actionHistory->setChecked(true);
	advanced = true;
	this->ui->actionAdvanced->setDisabled(true);
	this->ui->menuTabs->setDisabled(true);

	//dataUp = new QPushButton;
	//dataDown = new QPushButton;
	otsuButton = new QPushButton;
	kapuraButton = new QPushButton;
	niblackButton = new QPushButton;
	bernsenButton = new QPushButton;
	subsurfButton = new QPushButton;
	distanceButton = new QPushButton;
	sDistanceButton = new QPushButton;
	//dataListView = new QListWidget;
	dataTree = new QTreeWidget;
	useOData = new QCheckBox;
	axesCB = new QCheckBox;
	foregroundSB = new QSpinBox;
	backgroundSB = new QSpinBox;
	dataCBox = new QComboBox;
	sigmaSubsurf = new QDoubleSpinBox;
	tauSubsurf = new QDoubleSpinBox;
	kSubsurf = new QDoubleSpinBox;
	testingButton = new QPushButton;
	delSelButton = new QPushButton;
	openWinButton = new QPushButton;
	resetViewButton = new QPushButton;
	twoDButton = new QPushButton;
	threeDButton = new QPushButton;
	bernsenButton = new QPushButton;
	niblackTimeStepSB = new QDoubleSpinBox;
	niblackMaskSB = new QSpinBox;
	bernsenMaskSB = new QSpinBox;
	screenshotButton = new QPushButton;
	defaultValuesButton = new QPushButton;
	thresholdInitConButton = new QPushButton;
	initialCBox = new QComboBox;
	colorCBox = new QComboBox;
	contour2DButton = new QPushButton;
	contour3DButton = new QPushButton;
	numCont3DSB = new QSpinBox;
	contour2DwIDButton = new QPushButton;
	contour3DwDButton = new QPushButton;
	differenceButton = new QPushButton;
	heatEqSB = new QDoubleSpinBox;
	heatEquationButton = new QPushButton;
	contour3DPButton = new QPushButton;
	contour3DPwDButton = new QPushButton;
	manOptContourButton = new QPushButton;
	rangeLab = new 	QLabel;
	contourZConSB = new QDoubleSpinBox;
	optContDispButton = new QPushButton;
	historyText = new QPlainTextEdit;
	// parent3D = new QTreeWidgetItem();
	// parent2D = new QTreeWidgetItem();

	axesCB->setChecked(false);
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

	connect(this->otsuButton, SIGNAL(clicked()), this, SLOT(otsuClicked()));
	connect(this->kapuraButton, SIGNAL(clicked()), this, SLOT(kapuraClicked()));
	connect(this->niblackButton, SIGNAL(clicked()), this, SLOT(niblackClicked()));
	connect(this->bernsenButton, SIGNAL(clicked()), this, SLOT(bernsenClicked()));
	connect(this->subsurfButton, SIGNAL(clicked()), this, SLOT(subsurfClicked()));
	connect(this->distanceButton, SIGNAL(clicked()), this, SLOT(actionDistFunc()));
	connect(this->sDistanceButton, SIGNAL(clicked()), this, SLOT(actionSignDistFunc()));
	connect(this->delSelButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
	connect(this->resetViewButton, SIGNAL(clicked()), this, SLOT(resetViewClicked()));
	connect(this->twoDButton, SIGNAL(clicked()), this, SLOT(twoDClicked()));
	connect(this->threeDButton, SIGNAL(clicked()), this, SLOT(threeDClicked()));
	connect(this->resetViewButton, SIGNAL(clicked()), this, SLOT(resetViewClicked()));
	connect(this->defaultValuesButton, SIGNAL(clicked()), this, SLOT(setDefaultValues()));
	connect(this->screenshotButton, SIGNAL(clicked()), this, SLOT(saveScreenShot()));
	connect(this->thresholdInitConButton, SIGNAL(clicked()), this, SLOT(thresholdInitConClicked()));
	connect(this->contour3DButton, SIGNAL(clicked()), this, SLOT(contour3DClicked()));
	connect(this->contour2DButton, SIGNAL(clicked()), this, SLOT(contour2DClicked()));
	connect(this->contour2DwIDButton, SIGNAL(clicked()), this, SLOT(contour2DwIDClicked()));
	connect(this->contour3DwDButton, SIGNAL(clicked()), this, SLOT(contour3DwDClicked()));
	connect(this->differenceButton, SIGNAL(clicked()), this, SLOT(differenceClicked()));
	connect(this->heatEquationButton, SIGNAL(clicked()), this, SLOT(heatEquationClicked()));
	connect(this->axesCB, SIGNAL(clicked(bool)), this, SLOT(AxesChange(bool)));
	connect(this->colorCBox, SIGNAL(currentIndexChanged(int)), this, SLOT(colorIndexChanged(int)));
	connect(this->contour3DPButton, SIGNAL(clicked()), this, SLOT(contour3DPClicked()));
	connect(this->contour3DPwDButton, SIGNAL(clicked()), this, SLOT(contour3DPwDClicked()));
	connect(this->manOptContourButton, SIGNAL(clicked()), this, SLOT(manOptContClicked()));
	connect(this->optContDispButton, SIGNAL(clicked()), this, SLOT(optContDispClicked()));
	connect(this->testingButton, SIGNAL(clicked()), this, SLOT(testClicked()));

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

	filePath = QApplication::applicationDirPath();
	QSettings settings(filePath, QSettings::NativeFormat);
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
			_vWidget.at(_vWidget.size() - 1)->setAreaSize(s->size());
		}
	}
	else {
		// standard event processing
		return QObject::eventFilter(obj, event);
	}

	return false;
}

void bioData::slotExit() {
	qApp->exit();
}

void bioData::actionClose() {
	qApp->exit();
}

void bioData::actionOpenFile() {
	QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open File"), "", tr("Portable Graymap (*.pgm)"));

	if (filePaths.isEmpty())
		return;
	else
		filePath = filePaths[0];

	for (int i = 0; i < filePaths.size(); i++) {
		initWin(filePaths[i]);
	}
}

void bioData::initWin(QString path) {
	if (path.isEmpty()) 
		return;

	source *tmpFile = new source();
	_file.resize(_file.size() + 1);
	_file.replace(_file.size() - 1, tmpFile);
	_file.at(_file.size() - 1)->load(path);
	QStringList list = filePath.split('/');
	fName = list[list.length() - 1].split('.')[0];

	viewerWidget *VWTmp = new viewerWidget();
	_vWidget.resize(_vWidget.size() + 1);
	_vWidget.replace(_vWidget.size() - 1, VWTmp);
	_vWidget.at(_vWidget.size() - 1)->setScrollArea();

	if (widget == nullptr) {
		//createFileDock(list[list.length() - 1], filePath, tmpFile->getWidth(), tmpFile->getHeight());
		createListDock();
		createFilter2DDock();
		createFilter3DDock();
		createOptions2DDock();
		createOptions3DDock();
		createHistoryLogDock();
		QMainWindow::tabifyDockWidget(filter2DDock, options2DDock);
		QMainWindow::tabifyDockWidget(filter2DDock, subsurfDock);
		QMainWindow::tabifyDockWidget(filter2DDock, options3DDock);
		QMainWindow::tabifyDockWidget(filter2DDock, historyDock);
	}
	historyText->appendPlainText("File name: " + fName);
	historyText->appendPlainText("File path: " + filePath);
	historyText->appendPlainText("Width: " + QString::number(tmpFile->getWidth()) + " Height: " + QString::number(tmpFile->getHeight()));
	widget = new QWidget(mdiArea);
	gridLayout = new QGridLayout(widget);
	dataTree->model()->removeColumns(0, dataTree->columnCount());
	parent2D = new QTreeWidgetItem();
	parent2D->setText(0, "2D");
	parent3D = new QTreeWidgetItem();
	parent3D->setText(0, "3D");
	// dataTree->model()->removeColumns(0, dataTree->columnCount());
	dataTree->addTopLevelItem(parent2D);
	dataTree->addTopLevelItem(parent3D);
	parent3D->setHidden(true);
	mdiArea->addSubWindow(widget);
	options3DDock->hide();
	options2DDock->hide();
	setDefaultValues();
	twoDButton->setChecked(true);
	//twoDClicked();
	_file.at(_file.size() - 1)->setPoints(tmpFile->getOrigData());
	gridLayout->addWidget(_vWidget.at(_vWidget.size() - 1)->getScrollArea());
	_vWidget.at(_vWidget.size() - 1)->setViewerWidget2D(tmpFile->getImageData(), tmpFile->getFileName(fName));

	// widget->setWindowTitle("Original Data");
	addSubItem(parent2D, fName + "_original_data");

	widget->show();
	widget->showMaximized();

	//window *winTmp = new window(scaleSpinBox_x->value(), scaleSpinBox_y->value(), scaleSpinBox_z->value(), colorSpinBox_min->value(), colorSpinBox_max->value(), colorComboBox->currentIndex());
	//_tabParam.resize(_tabParam.size() + 1);
	//_tabParam.replace(_tabParam.size() - 1, tabTmp);
	/*_tabParam.at(_tabParam.size() - 1)->addListData("Original data");
	_tabParam.at(_tabParam.size() - 1)->addFileInfo("");

	auto tabWidget = new QWidget;
	tabWidget->setLayout(gridLayout);
	// pridanie prazdneho tabu do ktoreho vlozime naplneny widget s horiz. layoutom
	_tabs->addTab(tabWidget, list[list.size() - 1].left(6));
	_tabs->setCurrentIndex(_tabs->count() - 1);

	_vData.at(_vData.size() - 1)->setPolyData(_vData.at(_vData.size() - 1)->getDataOrig());
	_vViewerWidget.at(_vViewerWidget.size() - 1)->setScalarBar(_vData.at(_vData.size() - 1)->getScalarBar());
	_vData.at(_vData.size() - 1)->setColorPolyData(_vData.at(_vData.size() - 1)->getDataOrig(), colorComboBox->currentIndex(), checkCol);

	_tabParam.at(currentTab)->addMinMax(_vData.at(currentTab)->getfiltmin(_vData.at(_vData.size() - 1)->getDataOrig()), _vData.at(currentTab)->getfiltmax(_vData.at(_vData.size() - 1)->getDataOrig()));

	/*QMessageBox mbox;
	mbox.setText("Min: " + QString::number(_tabParam.at(currentTab)->getMin(0)) + "\nMax: " + QString::number(_tabParam.at(currentTab)->getMax(0)));
	mbox.exec();*/

	//_vViewerWidget.at(_vViewerWidget.size() - 1)->setViewerWidget(_vData.at(_vData.size() - 1)->getPolyData(), fName);
	//dataListView->setCurrentRow(0);

}

void bioData::addSubItem(QTreeWidgetItem *parent, QString name) {
	if (parent->isHidden())
		parent->setHidden(false);
	QTreeWidgetItem *itm = new QTreeWidgetItem();
	itm->setText(0, name);
	parent->addChild(itm);
	dataTree->setCurrentItem(itm);
}

// save pgm file
void bioData::actionpgm() {
	if (parent2D == dataTree->currentItem()->parent()) {
		int i = dataTree->currentItem()->indexOfChild(dataTree->currentItem());
		QString tmp = dataTree->currentItem()->text(0) + ".pgm";
		QString fileName1 = QFileDialog::getSaveFileName(this, tr("Save File"),
			tmp,
			tr("Images (*.pgm)"));
		cout << fileName1.toStdString() << endl;
		fTmp->save_ascii(fileName1, dataTree->currentIndex().row());
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR");
		mbox.exec();
	}
}

// save 3D vtk binary.
void bioData::action3Dvtkbinary() {
	if (parent3D == dataTree->currentItem()->parent()) {
		int i = dataTree->currentItem()->indexOfChild(dataTree->currentItem());
		QString tmp = dataTree->currentItem()->text(0) + ".vtp";
		QString fileName1 = QFileDialog::getSaveFileName(this, tr("Save File"),
			tmp,
			tr("VTK Files (*.vtk *.vtp)"));
		cout << fileName1.toStdString() << endl;
		_file.at(_file.size() - 1)->saveVtk3D(fileName1, dataTree->currentIndex().row(), true);
		//fTmp->save_ascii(fileName1, dataTree->currentIndex().row());
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR");
		mbox.exec();
	}
}

// save 3D vtk ascii.
void bioData::action3Dvtkascii() {
	if (parent3D == dataTree->currentItem()->parent()) {
		int i = dataTree->currentItem()->indexOfChild(dataTree->currentItem());
		QString tmp = dataTree->currentItem()->text(0) + ".vtp";
		QString fileName1 = QFileDialog::getSaveFileName(this, tr("Save File"),
			tmp,
			tr("VTK Files (*.vtk *.vtp)"));
		cout << fileName1.toStdString() << endl;
		_file.at(_file.size() - 1)->saveVtk3D(fileName1, dataTree->currentIndex().row(), false);
		//fTmp->save_ascii(fileName1, dataTree->currentIndex().row());
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR");
		mbox.exec();
	}
}

// save 2D vtk binary.
void bioData::action2Dvtkbinary() {
	if (parent2D == dataTree->currentItem()->parent()) {
		int i = dataTree->currentItem()->indexOfChild(dataTree->currentItem());
		QString tmp = dataTree->currentItem()->text(0) + ".vtp";
		QString fileName1 = QFileDialog::getSaveFileName(this, tr("Save File"),
			tmp,
			tr("VTK Files (*.vtk *.vtp)"));
		cout << fileName1.toStdString() << endl;
		_file.at(_file.size() - 1)->saveVtk2D(fileName1, dataTree->currentIndex().row(), true);
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR");
		mbox.exec();
	}
}

// save 2D vtk ascii.
void bioData::action2Dvtkascii() {
	if (parent2D == dataTree->currentItem()->parent()) {
		int i = dataTree->currentItem()->indexOfChild(dataTree->currentItem());
		QString tmp = dataTree->currentItem()->text(0) + ".vtp";
		QString fileName1 = QFileDialog::getSaveFileName(this, tr("Save File"),
			tmp,
			tr("VTK Files (*.vtk *.vtp)"));
		cout << fileName1.toStdString() << endl;
		_file.at(_file.size() - 1)->saveVtk2D(fileName1, dataTree->currentIndex().row(), false);
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR");
		mbox.exec();
	}
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
			filter2DDock->show();
			fileDock->show();
			subsurfDock->show();
			historyDock->show();
			this->ui->actionFileInfo->setChecked(true);
			this->ui->actionData->setChecked(true);
			this->ui->action2DFilters->setChecked(true);
			this->ui->action3DFilters->setChecked(true);
			this->ui->actionHistory->setChecked(true);
		}
		else if (!(this->ui->actionAll->isChecked())) {
			listDock->hide();
			filter2DDock->hide(); 
			fileDock->hide();
			subsurfDock->hide();
			historyDock->hide();
			this->ui->actionFileInfo->setChecked(false);
			this->ui->actionData->setChecked(false);
			this->ui->action2DFilters->setChecked(false);
			this->ui->action3DFilters->setChecked(false);
			this->ui->actionHistory->setChecked(false);
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

void bioData::action2DFilters() {

	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->action2DFilters->isChecked()) {
			filter2DDock->show();
		}
		else if (!(this->ui->action2DFilters->isChecked())) {
			filter2DDock->hide();
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::action3DFilters() {
	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->action3DFilters->isChecked()) {
			subsurfDock->show();
		}
		else if (!(this->ui->action3DFilters->isChecked())) {
			subsurfDock->hide();
		}
		else {
			mbox.setText("something went wrong!");
			mbox.exec();
		}
	}
}

void bioData::actionHistLog() {
	QMessageBox mbox;
	if (filePath.isEmpty()) {
		return;
	}
	else {
		if (this->ui->action3DFilters->isChecked()) {
			filter3DDock->show();
		}
		else if (!(this->ui->action3DFilters->isChecked())) {
			filter3DDock->hide();
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
	// listLayout->addWidget(Label, 2, 0, 2, 1);
	// listLayout->addWidget(useOData, 2, 1, 2, 1);
	delSelButton->setText("DELETE SELECTED");
	openWinButton->setText("OPEN IN NEW WINDOW");
	resetViewButton->setText("RESET VIEW");
	resetViewButton->setToolTip("Or Press R on keyboard.");
	screenshotButton->setText("SAVE SCREENSHOT");
	defaultValuesButton->setText("SET DEFAULT VALUES");
	defaultValuesButton->setToolTip("Sets options for all filters to default values.");
	twoDButton->setText("2D");
	twoDButton->setCheckable(true);
	threeDButton->setText("3D");
	threeDButton->setCheckable(true);
	openWinButton->setDisabled(true);
	QHBoxLayout *tmplayout = new QHBoxLayout();
	tmplayout->addWidget(twoDButton);
	tmplayout->addWidget(threeDButton);

	listLayout->addWidget(resetViewButton, 2, 0);
	listLayout->addLayout(tmplayout,2,1);
	listLayout->addWidget(delSelButton, 3, 0);
	listLayout->addWidget(openWinButton, 3, 1);
	listLayout->addWidget(screenshotButton, 4, 0);
	listLayout->addWidget(defaultValuesButton, 4, 1);

	multiWidget->setLayout(listLayout);
	listDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, listDock);
}

void bioData::createFilter2DDock() {
	filter2DDock = new QDockWidget(tr("Thresholding"), this);
	filter2DDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	filter2DDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);

	QWidget* multiWidget = new QWidget();
	QGridLayout *filterLayout = new QGridLayout;
	
	createGlobThrshldGB();
	createLocThrshldGB();

	filterLayout->addWidget(globThreshGroupBox);
	filterLayout->addWidget(locThreshGroupBox);
	   	 
	multiWidget->setLayout(filterLayout);
	filter2DDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, filter2DDock);
}

void bioData::createFilter3DDock() {
	subsurfDock = new QDockWidget(tr("3D Filters"), this);
	subsurfDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	subsurfDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* multiWidget = new QWidget();
	QGridLayout *filterLayout = new QGridLayout;
	initialConditionsGB();
	createSubsurfGB();
	// createtestGB();
	filterLayout->addWidget(initConGroupBox);
	filterLayout->addWidget(subsurfGroupBox);
	//filterLayout->addWidget(testGroupBox);
	multiWidget->setLayout(filterLayout);
	subsurfDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, subsurfDock);
}

void bioData::otsuClicked() {

	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	int otsuThr = filter.otsuFilter();
	_file.at(_file.size() - 1)->addFiltData(filter.createNewData(_file.at(_file.size() - 1)->getOrigData(), otsuThr));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	historyText->appendPlainText("Otsu's threshold: " + QString::number(otsuThr));
	//if (widget == nullptr)
	//	set2DWidget();
	//else
		update2DWidget();
	// Set the window title
	widget->setWindowTitle("Otsu Threshold");
	addSubItem(parent2D, fName + "_otsu");
	//QString item = "otsu";
	//dataListView->addItem(item);
    //dataListView->setCurrentRow(dataListView->count() - 1);
	//std::cout << "size of filt data: " << fTmp->getSizeFiltData() << std::endl;
	//fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
	/*widget2D->setWindowTitle("Otsu Threshold");
	w->updateViewerWidget2D();
	widget2D->update();*/
}

void bioData::kapuraClicked() {

	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	int kapurThr = filter.kapuraFilter();
	_file.at(_file.size() - 1)->addFiltData(filter.createNewData(_file.at(_file.size() - 1)->getOrigData(), kapurThr));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	historyText->appendPlainText("Maximum entropy threshold: " + QString::number(kapurThr));
	// if (widget2D == nullptr)
	//	set2DWidget();
	// else
	update2DWidget();
	widget->setWindowTitle("kapur");
	addSubItem(parent2D, fName + "_kapur");
}

void bioData::niblackClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData(),niblackMaskSB->value());
	QVector<unsigned char> tmp = filter.dataToChar(filter.niblackThreshold(filter.changeRangeOfData(filter.dataToInt(_file.at(_file.size() - 1)->getOrigData())), niblackTimeStepSB->value()));
	_file.at(_file.size() - 1)->addFiltData(tmp);
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	// if (widget2D == nullptr)
	// 	set2DWidget();
	// else
	update2DWidget();
	widget->setWindowTitle("niblack");
	addSubItem(parent2D, fName + "_niblack");
}

void bioData::listIndexChanged(int i)
{
	if (i == -1)
		return;
	else {
		QMessageBox mbox;
		mbox.setText("index changed");
		mbox.exec();
		_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(i));
		_vWidget.at(_vWidget.size() - 1)->updateViewerWidget2D();
	}
}

void bioData::treeIndexChanged(QTreeWidgetItem *itm, int i) {
		if (itm->parent() == parent2D) {
			_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()));
			options2DDock->show();
			options3DDock->hide();
			_vWidget.at(_vWidget.size() - 1)->updateViewerWidget2D();
			twoDClicked();
		}
		else if (itm->parent() == parent3D) {
			_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
			options2DDock->hide();
			options3DDock->show();
			_vWidget.at(_vWidget.size() - 1)->updateViewerWidget3D();
			threeDClicked();
		}
}

void bioData::bernsenClicked() {

	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData(), bernsenMaskSB->value());
	QVector<double> tmp = filter.bernsenThreshold(filter.dataToDouble(_file.at(_file.size() - 1)->getOrigData()));
	//QVector<double> tmp = filter.boundary(filter.dataToDouble(fTmp->getOrigData()), filter.otsuFilter());
	_file.at(_file.size() - 1)->addFiltData(filter.dataToChar(tmp));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));

	// if (widget2D == nullptr)
	//	set2DWidget();
	// else
	update2DWidget();
	widget->setWindowTitle("Bernsen");
	addSubItem(parent2D, fName + "_bernsen");
	
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

void bioData::subsurfClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
		QVector<double> tmp;
		if (initialCBox->currentIndex() == 0) {
			tmp = filter.subSurf(
				filter.distFunctSign(
					filter.dataToDouble(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()))),
				filter.changeRangeOfData(
					filter.dataToInt(filter.dataDifference((_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()))))),
				sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value());
		} else if (initialCBox->currentIndex() == 1) {
			tmp = filter.subSurf(
				filter.thresholdFunction(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())),
				filter.changeRangeOfData(
					filter.dataToInt(filter.dataDifference(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())))),
				sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value());
		}
		_file.at(_file.size() - 1)->add3DData(tmp);
		_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(_file.at(_file.size() - 1)->getSize3DData() - 1));
		_file.at(_file.size() - 1)->colorPolyData(colorCBox->currentIndex());
		_vWidget.at(_vWidget.size() - 1)->setViewerWidget3D(_file.at(_file.size() - 1)->getPolydata());
		_file.at(_file.size() - 1)->addZMinandMax();
		options3DDock->show();
		options2DDock->hide();
		QString lab;
		int i = dataTree->currentIndex().row();
		lab = "SUBSURF\nMaximum z coordinate: " + QString::number(_file.at(_file.size() - 1)->getZMax(i)) +
			"\nMinimum z coordinate: " + QString::number(_file.at(_file.size() - 1)->getZMin(i));
		// historyText->appendPlainText(lab);

		widget->setWindowTitle("Subsurf(3D)");
		QString txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
		addSubItem(parent3D, txt + "_subsurf");
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR! \nYou can't apply SUBSURF on 3D data.");
		mbox.exec();
	}
}

void bioData::actionDistFunc() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	QVector<double> tmp = filter.distFunct(filter.dataToDouble(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())));
	_file.at(_file.size() - 1)->add3DData(tmp);
	_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(_file.at(_file.size() - 1)->getSize3DData() - 1));
	_file.at(_file.size() - 1)->colorPolyData(colorCBox->currentIndex());
	_vWidget.at(_vWidget.size() - 1)->setViewerWidget3D(_file.at(_file.size() - 1)->getPolydata());
	options3DDock->show();
	options2DDock->hide();

		update3DWidget();
	// Set the window title
	widget->setWindowTitle("Distanced Function");
	QString txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
	addSubItem(parent3D, txt + "_dist_function");
}

void bioData::set3DWidget() {
//	widget3D = new QWidget(mdiArea);
	parent3D = new QTreeWidgetItem();
	threeDButton->setChecked(true);
	twoDButton->setChecked(false);
	parent3D->setText(0, "3D");
	parent3D->setExpanded(true);
	dataTree->addTopLevelItem(parent3D);
//	w->setScrollArea3D();
//	gridLayout3D = new QGridLayout(widget2D); 
//	gridLayout3D->addWidget(w->getScrollArea3D());
	_vWidget.at(_vWidget.size() - 1)->setViewerWidget3D(_file.at(_file.size() - 1)->getPolydata());
	options2DDock->hide();
	options3DDock->show();
	filter2DDock->show();
	setRangeValLab();
	// Adding a widget as a sub window in the Mdi Area
//	mdiArea->addSubWindow(widget3D);
//	mdiArea->setAttribute(Qt::WA_DeleteOnClose);
//	mdiArea->setWindowFlags(Qt::WindowTitleHint);
	// And show the widget
//	widget3D->show();
//	widget3D->showMaximized();
}

void bioData::update3DWidget() {
	_vWidget.at(_vWidget.size() - 1)->updateViewerWidget3D();
	options3DDock->show();
	options2DDock->hide();
	threeDClicked();
}

void bioData::update2DWidget() {
	_vWidget.at(_vWidget.size() - 1)->updateViewerWidget2D();
	options2DDock->show();
	options3DDock->hide();
	twoDClicked();
}

void bioData::actionSignDistFunc() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	QVector<double> tmp = filter.distFunctSign(filter.dataToDouble(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()))); // treba opravit
	_file.at(_file.size() - 1)->add3DData(tmp);
	_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(_file.at(_file.size() - 1)->getSize3DData() - 1));
	_file.at(_file.size() - 1)->colorPolyData(colorCBox->currentIndex());
	_vWidget.at(_vWidget.size() - 1)->setViewerWidget3D(_file.at(_file.size() - 1)->getPolydata());
	options3DDock->show();
	options2DDock->hide();

	// if (widget3D == nullptr)
	//	set3DWidget();
	// else
		update3DWidget();
	// Set the window title
	widget->setWindowTitle("Sign Distanced Function");	
	addSubItem(parent3D, "_sign_dist_function");
}

void bioData::createSubsurfGB() {
	subsurfGroupBox = new QGroupBox(tr("SUBSURF"));

	QGridLayout *subsurfLayout = new QGridLayout;
	QLabel *sigmaLabel = new QLabel(tr("Size of (linear) time steps:"));
	QLabel *tauLabel = new QLabel(tr("Size of (non-linear) time steps:"));
	QLabel *kLabel = new QLabel(tr("Sensitivity coeficient:"));
	QLabel *initConLabel = new QLabel(tr("Initial condition:"));

	initialCBox->addItems(QStringList() << "Sign distance function"  << "Result of threshold function");
	colorCBox->addItems(QStringList() << "Black & White" << "Rainbow");

	subsurfLayout->addWidget(initConLabel, 1, 0);
	subsurfLayout->addWidget(initialCBox, 1, 1);
	subsurfLayout->addWidget(sigmaLabel, 2, 0);
	subsurfLayout->addWidget(sigmaSubsurf, 2, 1);
	subsurfLayout->addWidget(tauLabel, 3, 0);
	subsurfLayout->addWidget(tauSubsurf, 3, 1);
	subsurfLayout->addWidget(kLabel, 4, 0);
	subsurfLayout->addWidget(kSubsurf, 4, 1);

	subsurfButton->setText("Apply");
	subsurfLayout->addWidget(subsurfButton, 5, 1);

	subsurfGroupBox->setLayout(subsurfLayout);
}

void bioData::initialConditionsGB() {
	initConGroupBox = new QGroupBox(tr("Initial Conditions"));

	QGridLayout *initConLayout = new QGridLayout;
	QLabel *distLab = new QLabel(tr("Distance function:"));
	QLabel *sDistLabel = new QLabel(tr("Sign distance function:"));
	QLabel *thresholdLabel = new QLabel(tr("Result of threshold function:"));

	distanceButton->setText("Apply");
	sDistanceButton->setText("Apply");
	thresholdInitConButton->setText("Apply");

	initConLayout->addWidget(distLab, 0,0);
	initConLayout->addWidget(distanceButton, 0, 1);
	initConLayout->addWidget(sDistLabel, 1, 0);
	initConLayout->addWidget(sDistanceButton, 1, 1);
	initConLayout->addWidget(thresholdLabel, 2, 0);
	initConLayout->addWidget(thresholdInitConButton, 2, 1);

	initConGroupBox->setLayout(initConLayout);
}

void bioData::createtestGB() {
	testGroupBox = new QGroupBox(tr("Testing"));

	QGridLayout *testLayout = new QGridLayout;
	testingButton->setText("testing");
	testLayout->addWidget(testingButton);

	testGroupBox->setLayout(testLayout);
}

void bioData::deleteClicked() {
	QMessageBox mbox;
	qApp->processEvents();

	// ak je v liste uz len jeden riadok, tak rovno zavrie cely tab
	if (dataTree->topLevelItemCount() == 1 && parent2D->childCount() == 1) {
		dataTree->model()->removeRow(dataTree->currentIndex().row());
		actionClose();
	}
	// delete selected
	else if (dataListView->currentRow() == 0) //Original data
	{
		mbox.setText("It is not possible to remove original data when list is not empty");
		mbox.exec();
	}
	else {
		dataTree->model()->removeRow(dataTree->currentIndex().row());
	}
}

void bioData::resetViewClicked () {
	_vWidget.at(_vWidget.size() - 1)->resetCam();
}

// nedokoncene
void bioData::actionCloseFiles() {
	qApp->processEvents();

	// vymaze aktualny tab
	if (mdiArea->subWindowList().length() > 0) //ak je pocet tabov vacsi ako 0
	{
		mdiArea->closeAllSubWindows();
		listDock->hide();
	}
	else {
		QMessageBox mbox;
		mbox.setText("ERROR! NO DATA ARE LOADED!");
		mbox.exec();
	}
}

void bioData::twoDClicked() {
	twoDButton->setChecked(true);
	threeDButton->setChecked(false);
	_vWidget.at(_vWidget.size() - 1)->set2DView();
	resetViewClicked();
}

void bioData::threeDClicked() {
	threeDButton->setChecked(true);
	twoDButton->setChecked(false);
	_vWidget.at(_vWidget.size() - 1)->set3DView();
}

void bioData::createGlobThrshldGB() {
	globThreshGroupBox = new QGroupBox(tr("Global histogram-based thresholding"));

	QGridLayout *layout = new QGridLayout;
	QLabel *otsuLabel = new QLabel(tr("Between-class variance:"));
	QLabel *kapurLabel = new QLabel(tr("Maximum entropy thresholding:"));

	otsuButton->setText("Apply");
	layout->addWidget(otsuLabel, 0, 0);
	layout->addWidget(otsuButton, 0, 1);
	kapuraButton->setText("Apply");
	layout->addWidget(kapurLabel, 1, 0);
	layout->addWidget(kapuraButton, 1, 1);

	globThreshGroupBox->setLayout(layout);
}

void bioData::createLocThrshldGB() {
	locThreshGroupBox = new QGroupBox(tr("Local adaptive thresholding"));

	QGridLayout *layout = new QGridLayout;
	QGroupBox *niblackGBox = new QGroupBox(tr("Niblack's  method"));
	QGridLayout *subNLayout = new QGridLayout;
	QLabel *timeStepLab = new QLabel(tr("Time step size:"));
	QLabel *niblackMaskLabel = new QLabel(tr("Mask size:"));
	niblackButton->setText("Apply");
	subNLayout->addWidget(timeStepLab, 1, 0);
	subNLayout->addWidget(niblackTimeStepSB, 1, 1);
	subNLayout->addWidget(niblackMaskLabel, 2, 0);
	subNLayout->addWidget(niblackMaskSB,2, 1);
	subNLayout->addWidget(niblackButton, 3, 1);
	niblackGBox->setLayout(subNLayout);

	QGroupBox *bernsenGBox = new QGroupBox(tr("Bernsen's method"));
	QGridLayout *subBLayout = new QGridLayout;
	QLabel *bernsenMaskLabel = new QLabel(tr("Mask size:"));
	bernsenButton->setText("Apply");
	subBLayout->addWidget(bernsenMaskLabel, 1, 0);
	subBLayout->addWidget(bernsenMaskSB, 1, 1);
	subBLayout->addWidget(bernsenButton, 3, 1);
	bernsenGBox->setLayout(subBLayout);

	layout->addWidget(niblackGBox);
	layout->addWidget(bernsenGBox);
	locThreshGroupBox->setLayout(layout);
}

void bioData::setDefaultValues() {
	// subsurf param
	sigmaSubsurf->setRange(0.0001, 1000.0);
	sigmaSubsurf->setDecimals(5);
	sigmaSubsurf->setSingleStep(0.01);
	sigmaSubsurf->setValue(0.25);
	tauSubsurf->setRange(0.0001, 1000.0);
	tauSubsurf->setDecimals(5);
	tauSubsurf->setSingleStep(0.01);
	tauSubsurf->setValue(1.0);
	kSubsurf->setRange(0.00001, 999999.0);
	kSubsurf->setDecimals(2);
	kSubsurf->setSingleStep(0.01);
	kSubsurf->setValue(255 * 255);

	// niblack param
	niblackTimeStepSB->setRange(0.0001, 1000.0);
	niblackTimeStepSB->setDecimals(5);
	niblackTimeStepSB->setSingleStep(0.1);
	niblackTimeStepSB->setValue(5.0);
	niblackMaskSB->setRange(1, 50);
	niblackMaskSB->setValue(6);
	
	// bernsen param
	bernsenMaskSB->setRange(1, 50);
	bernsenMaskSB->setValue(1);

	//contours 
	numCont3DSB->setRange(1, 1000);
	numCont3DSB->setValue(10);
	//contour val
	contourZConSB->setRange(-100, 100);
}

void bioData::saveScreenShot() {
	_vWidget.at(_vWidget.size() - 1)->saveScreenShot();
}

void bioData::thresholdInitConClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	QVector<double> tmp = filter.thresholdFunction(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()));
	_file.at(_file.size() - 1)->add3DData(tmp);
	_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(_file.at(_file.size() - 1)->getSize3DData() - 1));
	_file.at(_file.size() - 1)->colorPolyData(colorCBox->currentIndex());
	_vWidget.at(_vWidget.size() - 1)->setViewerWidget3D(_file.at(_file.size() - 1)->getPolydata());

	widget->setWindowTitle("Threshold Function");
	QString txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
	addSubItem(parent3D, txt + "_threshold_function");
}

void bioData::createOptions2DDock() {
	options2DDock = new QDockWidget(tr("2D Options"), this);
	options2DDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	options2DDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* multiWidget = new QWidget();
	QGridLayout *layout = new QGridLayout; 
	QLabel *differenceLab = new QLabel(tr("Aritmetic mean:"));
	QLabel *heLab = new QLabel(tr("One step of Heat Equation:"));
	QLabel *originalDataLab = new QLabel(tr("Process original data:"));
	differenceLab->setToolTip("Creates new boundary condition for the segmentation.\n Takes 1/2 of the selected thresholded data and 1/2 and makes mean.");
	differenceButton->setText("Apply");
	createcontour2DGB();
	createHeatEqGB();

	layout->addWidget(differenceLab, 1, 0);
	layout->addWidget(differenceButton, 1, 1);
	layout->addWidget(HeatEqGroupBox,2,0,1,2);
	layout->addWidget(contour2DGroupBox, 3, 0,1,2);
	multiWidget->setLayout(layout);
	options2DDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, options2DDock);
}
 
void bioData::createOptions3DDock() {
	options3DDock = new QDockWidget(tr("3D Options"), this);
	options3DDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	options3DDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);

	QWidget* multiWidget = new QWidget();
	QGridLayout *layout = new QGridLayout;
	QLabel *AxesLab = new QLabel(tr("Axes: "));
	QLabel *colorLab = new QLabel(tr("Colors: "));

	createcontour3DGB();
	createtestGB();
	createrManOptContourGB();
	layout->addWidget(AxesLab,0, 0);
	layout->addWidget(axesCB, 0, 1);
	layout->addWidget(colorLab, 1, 0);
	layout->addWidget(colorCBox, 1, 1);
	layout->addWidget(contour3DGroupBox,2,0,1,2);
	layout->addWidget(manOptContourGB, 3, 0, 1, 2);
	//layout->addWidget(testGroupBox, 4, 0, 1, 2);
	multiWidget->setLayout(layout);
	options3DDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, options3DDock);
}

void bioData::createHeatEqGB() {
	HeatEqGroupBox = new QGroupBox(tr("Heat Equation"));

	QGridLayout *layout = new QGridLayout;
	QLabel *HeatEqTimeStepLab = new QLabel(tr("Time Step: "));
	heatEquationButton->setText("Show");
	layout->addWidget(HeatEqTimeStepLab, 1, 0);
	layout->addWidget(heatEqSB, 1, 1);
	layout->addWidget(heatEquationButton, 2, 1);

	HeatEqGroupBox->setLayout(layout);
}

void bioData::createHistoryLogDock() {
	historyDock = new QDockWidget(tr("History Logs"), this);
	historyDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	historyDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* multiWidget = new QWidget();
	QGridLayout *layout = new QGridLayout;
	historyText->setReadOnly(true);
	layout->addWidget(historyText);

	multiWidget->setLayout(layout);
	historyDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, historyDock);
}

void bioData::contour3DClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());

		_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(_vWidget.size() - 1)->contours3D(_file.at(_file.size() - 1)->getPolydata(), numCont3DSB->value(), false);
		widget->update();
	}
}

void bioData::createcontour3DGB() {
	contour3DGroupBox = new QGroupBox(tr("Contours"));

	QGridLayout *layout = new QGridLayout;
	QLabel *contourLab = new QLabel(tr("Number of contours:"));
//	QLabel *contourLab1 = new QLabel(tr("Only contours(scalars):"));
//	QLabel *contourLab2 = new QLabel(tr("Contours on data(scalars):"));
//	QLabel *contourLab3 = new QLabel(tr("Only contours(plane):"));
//	QLabel *contourLab4 = new QLabel(tr("Contours on data(plane):"));

	QLabel *contourLab3 = new QLabel(tr("Only contours:"));
	QLabel *contourLab4 = new QLabel(tr("Contours on data:"));

	contour3DButton->setText("Show");
	contour3DwDButton->setText("Show");
	contour3DPButton->setText("Show");
	contour3DPwDButton->setText("Show");
	layout->addWidget(contourLab, 0, 0);
	layout->addWidget(numCont3DSB, 0, 1);
	// layout->addWidget(contourLab1, 1, 0);
	// layout->addWidget(contour3DButton, 1, 1);
	// layout->addWidget(contourLab2, 2, 0);
	// layout->addWidget(contour3DwDButton, 2, 1);
	layout->addWidget(contourLab3, 3, 0);
	layout->addWidget(contour3DPButton, 3, 1);
	layout->addWidget(contourLab4, 4, 0);
	layout->addWidget(contour3DPwDButton, 4, 1);
	contour3DGroupBox->setLayout(layout);
}

void bioData::createcontour2DGB() {
	contour2DGroupBox = new QGroupBox(tr("Contours"));

	QGridLayout *layout = new QGridLayout;
	QLabel *Lab = new QLabel(tr("Only contour: "));
	QLabel *Lab1 = new QLabel(tr("Contour on data: "));
	contour2DButton->setText("Show");
	contour2DwIDButton->setText("Show");
	layout->addWidget(Lab,0,0);
	layout->addWidget(contour2DButton,0,1);
	layout->addWidget(Lab1,1,0);
	layout->addWidget(contour2DwIDButton, 1, 1);

	contour2DGroupBox->setLayout(layout);
}

void bioData::contour2DClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
		_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()));
		_vWidget.at(_vWidget.size() - 1)->contours2D(_file.at(_file.size() - 1)->getImageData(), false);
	}
}

void bioData::contour2DwIDClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
		_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row()));
		_vWidget.at(_vWidget.size() - 1)->contours2D(_file.at(_file.size() - 1)->getImageData());
	}
}

void bioData::contour3DwDClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());

		_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(_vWidget.size() - 1)->contours3D(_file.at(_file.size() - 1)->getPolydata(), numCont3DSB->value());
		widget->update();
	}
}

void bioData::differenceClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	_file.at(_file.size() - 1)->addFiltData(filter.dataDifference(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	//if (widget2D == nullptr)
	//	set2DWidget();
	//else
		update2DWidget();
	// Set the window title
	widget->setWindowTitle("Aritmetic mean");
	addSubItem(parent2D, fName + "_aritmetic_mean");
	// fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
}

void bioData::heatEquationClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	_file.at(_file.size() - 1)->addFiltData(filter.dataToChar(filter.antireflection(filter.heatImpl(filter.dataToDouble(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())), heatEqSB->value()))));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	// if (widget2D == nullptr)
	//	set2DWidget();
	//else
		update2DWidget();
	// Set the window title
	widget->setWindowTitle("Heat Equation");
	addSubItem(parent2D, fName + "_heatEq");
	// fTmp->setPoints(fTmp->getFiltData(fTmp->getSizeFiltData() - 1));
}

void bioData::AxesChange(bool checked) {
	if (parent3D == dataTree->currentItem()->parent()) 
		if (checked) {
			filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
			_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
			_vWidget.at(_vWidget.size() - 1)->addAxes(_file.at(_file.size() - 1)->getPolydata());
			widget->update();
		}
		else {
			_vWidget.at(_vWidget.size() - 1)->removeAxes();
			widget->update();
		}
}

void bioData::colorIndexChanged(int i) {
	if (parent3D != nullptr)
		if( parent3D == dataTree->currentItem()->parent()) {
			_file.at(_file.size() - 1)->colorPolyData(i);
			_vWidget.at(_vWidget.size() - 1)->updateViewerWidget3D();
		}
}

void bioData::contour3DPClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());

		_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(_vWidget.size() - 1)->cutContour(_file.at(_file.size() - 1)->getPolydata(), numCont3DSB->value(), false);
		widget->update();
	}
}

void bioData::contour3DPwDClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());

		_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(_vWidget.size() - 1)->cutContour(_file.at(_file.size() - 1)->getPolydata(), numCont3DSB->value());
		widget->update();
	}

}

void bioData::testClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
	_vWidget.at(_vWidget.size() - 1)->cut1Contour(_file.at(_file.size() - 1)->getPolydata(), contourZConSB->value(),true);
	_file.at(_file.size() - 1)->addFiltData(filter.dataDifference(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	_vWidget.at(_vWidget.size() - 1)->optContourOnID(contourZConSB->value());
	widget->update();
	twoDClicked();
}

void bioData::createrManOptContourGB() {
	manOptContourGB = new QGroupBox(tr("Find optimal contour (manually)"));

	QGridLayout *layout = new QGridLayout;
	QLabel *zLab = new QLabel(tr("Z coordinate of contour: "));
	QLabel *ogDataLab = new QLabel(tr("Display on original data: "));
	//setRangeValLab();
	manOptContourButton->setText("Show");
	optContDispButton->setText("Show");
	// layout->addWidget(rangeLab, 0, 0, 1, 2);
	layout->addWidget(zLab, 0, 0);
	layout->addWidget(contourZConSB, 0, 1);
	layout->addWidget(manOptContourButton, 1, 1);
	layout->addWidget(ogDataLab, 2, 0);
	layout->addWidget(optContDispButton, 2, 1);

	manOptContourGB->setLayout(layout);
}

void bioData::manOptContClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
	_vWidget.at(_vWidget.size() - 1)->cut1Contour(_file.at(_file.size() - 1)->getPolydata(), contourZConSB->value());
	// _vWidget.at(_vWidget.size() - 1)->optContourOnID();
	widget->update();
}

void bioData::setRangeValLab() {
	if (parent3D != nullptr)
		if (parent3D == dataTree->currentItem()->parent()) {
			QString lab;
			int i = dataTree->currentIndex().row();
			lab = "Maximum z coordinate: " + QString::number(_file.at(_file.size() - 1)->getZMax(i)) +
				"\nMinimum z coordinate: " + QString::number(_file.at(_file.size() - 1)->getZMin(i));
			contourZConSB->setMaximum(_file.at(_file.size() - 1)->getZMax(i));
			contourZConSB->setMinimum(_file.at(_file.size() - 1)->getZMin(i));
			contourZConSB->setValue(round(_file.at(_file.size() - 1)->getZMax(i)));
			rangeLab->setText(lab);
		}
}

void bioData::optContDispClicked() {
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData());
	_file.at(_file.size() - 1)->create3Ddata(_file.at(_file.size() - 1)->get3DData(dataTree->currentIndex().row()));
	_vWidget.at(_vWidget.size() - 1)->cut1Contour(_file.at(_file.size() - 1)->getPolydata(), contourZConSB->value(), true);
	_file.at(_file.size() - 1)->addFiltData(filter.dataDifference(_file.at(_file.size() - 1)->getFiltData(dataTree->currentIndex().row())));
	_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	_vWidget.at(_vWidget.size() - 1)->optContourOnID(contourZConSB->value());
	dataTree->setCurrentItem(parent2D->child(0));
	twoDClicked();
}