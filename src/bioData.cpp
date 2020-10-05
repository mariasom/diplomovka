#include "bioData.h"

bioData::bioData(QWidget *parent)
{
	this->ui = new Ui::bioData;
	this->ui->setupUi(this);

	dataTree = new QTreeWidget; 
	progBar = new QProgressBar;
	winListView = new QListWidget;

	// new buttons for GUI
	otsuButton = new QPushButton;
	kapuraButton = new QPushButton;
	niblackButton = new QPushButton;
	bernsenButton = new QPushButton;
	subsurfButton = new QPushButton;
	distanceButton = new QPushButton;
	sDistanceButton = new QPushButton;
	delSelButton = new QPushButton;
	openWinButton = new QPushButton;
	resetViewButton = new QPushButton;
	twoDButton = new QPushButton;
	threeDButton = new QPushButton;
	bernsenButton = new QPushButton;
	testingButton = new QPushButton;
	delSelButton = new QPushButton;
	openWinButton = new QPushButton;
	resetViewButton = new QPushButton;
	twoDButton = new QPushButton;
	threeDButton = new QPushButton;
	bernsenButton = new QPushButton;
	screenshotButton = new QPushButton;
	defaultValuesButton = new QPushButton;
	thresholdInitConButton = new QPushButton;
	contour2DButton = new QPushButton;
	contour3DButton = new QPushButton;
	contour2DwIDButton = new QPushButton;
	contour3DwDButton = new QPushButton;
	differenceButton = new QPushButton;
	heatEquationButton = new QPushButton;
	contour3DPButton = new QPushButton;
	contour3DPwDButton = new QPushButton;
	manOptContourButton = new QPushButton;
	optContDispButton = new QPushButton;
	histSaveButton = new QPushButton;
	cutDataAtButton = new QPushButton;
	hybNBABernButton = new QPushButton;
	sauvolaButton = new QPushButton;
	hybSaBernButton = new QPushButton;
	deleteWinButton = new QPushButton;
	zlepsiVectorFieldButton = new QPushButton;

	// axes
	useOData = new QCheckBox;
	axesCB = new QCheckBox;

	// spinboxes
	sigmaSubsurf = new QDoubleSpinBox;
	tauSubsurf = new QDoubleSpinBox;
	kSubsurf = new QDoubleSpinBox;
	niblackTimeStepSB = new QDoubleSpinBox;
	contourZConSB = new QDoubleSpinBox;
	heatEqSB = new QDoubleSpinBox;
	cutDataAtSB = new QDoubleSpinBox;
	NBaBrenTimeStepSB = new QDoubleSpinBox;
	sauvolaTimeStepSB = new QDoubleSpinBox;
	SaBrenTimeStepSB = new QDoubleSpinBox;

	niblackMaskSB = new QSpinBox;
	bernsenMaskSB = new QSpinBox;
	numCont3DSB = new QSpinBox;	
	NBaBrenMaskSB = new QSpinBox;
	timeStepsSubsurf = new QSpinBox;
	sauvolaMaskSB = new QSpinBox;
	SaBrenMaskSB = new QSpinBox;

	dataCBox = new QComboBox;
	initialCBox = new QComboBox;
	colorCBox = new QComboBox;
	gradTypeCBox = new QComboBox;

	rangeLab = new 	QLabel;
	historyText = new QPlainTextEdit;

	axesCB->setChecked(false);
	useOData->setChecked(true);
	// useOData->setDisabled(true);

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
	connect(this->optContDispButton, SIGNAL(clicked()), this, SLOT(optContDispClicked()));
	connect(this->histSaveButton, SIGNAL(clicked()), this, SLOT(histSavedClicked()));
	connect(this->cutDataAtButton, SIGNAL(clicked()), this, SLOT(cutDataAtClicked()));
	connect(this->hybNBABernButton, SIGNAL(clicked()), this, SLOT(hybNBABernClicked()));
	connect(this->sauvolaButton, SIGNAL(clicked()), this, SLOT(sauvolaClicked()));
	connect(this->hybSaBernButton, SIGNAL(clicked()), this, SLOT(hybSaBernClicked()));
	connect(this->deleteWinButton, SIGNAL(clicked()), this, SLOT(deleteWinClicked()));
	connect(this->zlepsiVectorFieldButton, SIGNAL(clicked()), this, SLOT(zlepsiVectorFieldClicked()));
	connect(this->openWinButton, SIGNAL(clicked()), this, SLOT(openWinClicked()));

	connect(this->testingButton, SIGNAL(clicked()), this, SLOT(testClicked()));
	connect(this->winListView, SIGNAL(currentRowChanged(int)), this, SLOT(listIndexChanged(int)));
	connect(this->dataTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(treeIndexChanged(QTreeWidgetItem *, int)));
	
	// space for the display area
	mdiArea = new QMdiArea(this); 
	// connect(this->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(subWinActivated(QMdiSubWindow*)));
	// configure scrollbars
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	// Set Mdi Area as the central widget
	setCentralWidget(mdiArea);

	// ui->statusbar->addPermanentWidget(progBar);

	createListDock();
	createFilter2DDock();
	createFilter3DDock();
	createOptions2DDock();
	createOptions3DDock();
	createHistoryLogDock();
	createWindowsDock();
	createHelpDock();
	QMainWindow::tabifyDockWidget(filter2DDock, options2DDock);
	QMainWindow::tabifyDockWidget(filter2DDock, subsurfDock);
	QMainWindow::tabifyDockWidget(filter2DDock, options3DDock);
	QMainWindow::tabifyDockWidget(filter2DDock, historyDock);
	QMainWindow::tabifyDockWidget(filter2DDock, windowsDock);
	QMainWindow::tabifyDockWidget(filter2DDock, helpDock);

	hideAllDocks();
	this->ui->actionAll->setChecked(true);
	disableMenuOpt();

	filePath = QApplication::applicationDirPath();
	QSettings settings(filePath, QSettings::NativeFormat);
}

void bioData::keyUpEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Up)
	{
		QMessageBox mbox;
		mbox.setText("key up stlaceny!");
		mbox.exec();
	}
}

void bioData::keyDownEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Down)
	{
		QMessageBox mbox;
		mbox.setText("key down stlaceny!");
		mbox.exec();
	}
}

bool bioData::eventFilter(QObject * obj, QEvent * event) {
	if (obj->objectName() == "QScrollArea") {
		QScrollAreaEventFilter(obj, event);
	}
	return false;
}

bool bioData::QScrollAreaEventFilter(QObject * obj, QEvent * event) {
	QScrollArea* s = static_cast<QScrollArea*>(obj);
	if (event->type() == QEvent::Resize) {
		if (s->widget()) {
			viewerWidget* w = static_cast<viewerWidget*>(s->widget());
			_vWidget.at(currentWin)->setAreaSize(s->size());
		}
	}
	else {
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
	QStringList filePaths = QFileDialog::getOpenFileNames(this, tr("Open File"), "", tr("All files(*.*);; Portable Graymap(*.pgm);; TIFF(*.tif)"));

	if (filePaths.isEmpty())
		return;
	else
		filePath = filePaths[0];

	ui->statusbar->showMessage("Loading...");
	qApp->processEvents();
	for (int i = 0; i < filePaths.size(); i++) {
		initWin(filePaths[i]);
	}
	ui->statusbar->clearMessage();
}

void bioData::initWin(QString path) {
	if (path.isEmpty()) 
		return;

	source *tmpFile = new source();
	_file.resize(_file.size() + 1);
	_file.replace(_file.size() - 1, tmpFile);
	if(path.contains(".pgm"))
		_file.at(_file.size() - 1)->load(path);
	else if (path.contains(".tif"))
		_file.at(_file.size() - 1)->readTifFile(path);
	else {

		return;
	}
	QStringList list = path.split('/');
	fName = list[list.length() - 1].split('.')[0];

	viewerWidget *VWTmp = new viewerWidget();
	_vWidget.resize(_vWidget.size() + 1);
	_vWidget.replace(_vWidget.size() - 1, VWTmp);
	_vWidget.at(_vWidget.size() - 1)->setScrollArea();

	historyText->clear();
	historyText->appendPlainText("File name: " + fName);
	historyText->appendPlainText("File path: " + path);
	historyText->appendPlainText("File type: " + _file.at(_file.size() - 1)->getText());
	historyText->appendPlainText("Width: " + QString::number(tmpFile->getWidth()) + " Height: " + QString::number(tmpFile->getHeight()));

	QMdiSubWindow *subWTmp = new QMdiSubWindow();
	_subW.resize(_subW.size() + 1);
	QWidget *widget = new QWidget();
	gridLayout = new QGridLayout(widget);
	dataTree->clear();
	parent2D = new QTreeWidgetItem();
	parent2D->setText(0, "2D");
	parent3D = new QTreeWidgetItem();
	parent3D->setText(0, "3D");
	dataTree->addTopLevelItem(parent2D);
	dataTree->addTopLevelItem(parent3D);
	parent3D->setHidden(true);
    _subW.replace(_subW.size() - 1, mdiArea->addSubWindow(widget));
	options3DDock->hide();
	options2DDock->hide();
	setDefaultValues();
	twoDButton->setChecked(true);
	_file.at(_file.size() - 1)->setPoints(tmpFile->getOrigData());
	gridLayout->addWidget(_vWidget.at(_vWidget.size() - 1)->getScrollArea());
	_vWidget.at(_vWidget.size() - 1)->setViewerWidget2D(tmpFile->getImageData(), tmpFile->getFileName(fName));

	enableMenuOpt();
	subWin *winTmp = new subWin(fName);
	_winParam.resize(_winParam.size() + 1);
	_winParam.replace(_winParam.size() - 1, winTmp);
	_winParam.at(_winParam.size() - 1)->add2DData(fName + "_original_data");
	_winParam.at(_winParam.size() - 1)->addHistInfo(historyText->toPlainText());
	winListView->addItem(fName);
	subWinAdded = true;
	winListView->setCurrentRow(winListView->count() - 1);
	_subW.at(currentWin)->setWindowTitle(fName);
	addSubItem(parent2D, fName + "_original_data");
	showAllDocks();
	if (winListView->count() == 1)
		windowsDock->hide();
	else 
		windowsDock->show();
	filter2DDock->raise();
	_subW.at(currentWin)->showMaximized();
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
			tr("Images Files(*.pgm)"));
		if (fileName1.isEmpty())
			return;
		_file.at(currentWin)->save_ascii(fileName1, dataTree->currentIndex().row());
	}
	else {
		errorMessages(1);
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
		if (fileName1.isEmpty())
			return;
		_file.at(currentWin)->saveVtk3D(fileName1, dataTree->currentIndex().row(), true);
	}
	else {
		errorMessages(2);
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
		if (fileName1.isEmpty())
			return;
		_file.at(currentWin)->saveVtk3D(fileName1, dataTree->currentIndex().row(), false);
	}
	else {
		errorMessages(2);
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
		if (fileName1.isEmpty())
			return;
		_file.at(currentWin)->saveVtk2D(fileName1, dataTree->currentIndex().row(), true);
	}
	else {
		errorMessages(1);
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
		if (fileName1.isEmpty())
			return;
		_file.at(currentWin)->saveVtk2D(fileName1, dataTree->currentIndex().row(), false);
	}
	else {
		errorMessages(1);
	}
}

// save screenshot
void bioData::saveScreenShot() {
	QString tmp = dataTree->currentItem()->text(0) + ".png";
	QString fn = QFileDialog::getSaveFileName(this, "Save file",
		tmp, 
		"Image Files(*.png *.jpg *.bmp)");
	if (fn.isEmpty())
		return;
	_vWidget.at(currentWin)->saveScreenShot(fn);
}

void bioData::actionAll() {
	if (filePath.isEmpty()) 
		return;
	else {
		if (this->ui->actionAll->isChecked()) 
			showAllDocks();
		else if (!(this->ui->actionAll->isChecked())) 
			hideAllDocks();
		else
			errorMessages(3);
	}
}

void bioData::actionData() {
	if (filePath.isEmpty()) 
		return;
	else {
		if (this->ui->actionData->isChecked()) 
			listDock->show();
		else if (!(this->ui->actionData->isChecked())) 
			listDock->hide();
		else 
			errorMessages(3);
	}
}

void bioData::action2DFilters() {
	if (filePath.isEmpty()) 
		return;
	else {
		if (this->ui->action2DFilters->isChecked()) 
			filter2DDock->show();
		else if (!(this->ui->action2DFilters->isChecked())) 
			filter2DDock->hide();
		else 
			errorMessages(3);
	}
}

void bioData::action3DFilters() {
	if (filePath.isEmpty()) 
		return;
	else {
		if (this->ui->action3DFilters->isChecked()) 
			subsurfDock->show();
		else if (!(this->ui->action3DFilters->isChecked())) 
			subsurfDock->hide();
		else 
			errorMessages(3);
	}
}

void bioData::actionHistLog() {
	if (filePath.isEmpty()) 
		return;
	else {
		if (this->ui->action3DFilters->isChecked()) 
			historyDock->show();
		else if (!(this->ui->action3DFilters->isChecked())) 
			historyDock->hide();
		else 
			errorMessages(3);
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

	QScrollArea* VerticalScrollArea = new QScrollArea;
	VerticalScrollArea->setWidgetResizable(true);
	QWidget* multiWidget = new QWidget();
	VerticalScrollArea->setWidget(multiWidget);
	QGridLayout *filterLayout = new QGridLayout(multiWidget);
	VerticalScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	
	createGlobThrshldGB();
	createLocThrshldGB();
	//createtestGB();

	filterLayout->addWidget(globThreshGroupBox);
	filterLayout->addWidget(locThreshGroupBox);
	//filterLayout->addWidget(testGroupBox);
	   	 
	multiWidget->setLayout(filterLayout);
	filter2DDock->setWidget(VerticalScrollArea);
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
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();		
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
	int otsuThr = filter.otsuFilter();
	_file.at(currentWin)->addFiltData(filter.createNewData(_file.at(currentWin)->getOrigData(), otsuThr));
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	historyText->appendPlainText("Otsu's threshold: " + QString::number(otsuThr));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_otsu");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_otsu");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::kapuraClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
	int kapurThr = filter.kapuraFilter();
	_file.at(currentWin)->addFiltData(filter.createNewData(_file.at(currentWin)->getOrigData(), kapurThr));
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	historyText->appendPlainText("Maximum entropy threshold: " + QString::number(kapurThr));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_kapur");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_kapur");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::niblackClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData(), niblackMaskSB->value());
	_winParam.at(currentWin)->changeNiblackParam(niblackTimeStepSB->value(), niblackMaskSB->value());
	QVector<unsigned char> tmp = filter.dataToChar(filter.niblackThreshold(filter.changeRangeOfData(filter.dataToInt(_file.at(currentWin)->getOrigData())), niblackTimeStepSB->value()));
	_file.at(currentWin)->addFiltData(tmp);
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_niblack");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_niblack");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::treeIndexChanged(QTreeWidgetItem *itm, int i) {
		if (itm->parent() == parent2D) {
			_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()));
			options2DDock->show();
			options3DDock->hide();
			_vWidget.at(currentWin)->updateViewerWidget2D();
			twoDClicked();
		}
		else if (itm->parent() == parent3D) {
			_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
			_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
			options2DDock->hide();
			options3DDock->show();

			if (axesCB->isChecked()) {
				_vWidget.at(currentWin)->addAxes(_file.at(currentWin)->getPolydata());
			}
			else {
				_vWidget.at(currentWin)->updateViewerWidget3D();
			}
			threeDClicked();
		}
		else
			errorMessages(3);
}

void bioData::bernsenClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData(), bernsenMaskSB->value());
	_winParam.at(currentWin)->changeBernsenParam(bernsenMaskSB->value());
	QVector<double> tmp = filter.bernsenThreshold(filter.dataToDouble(_file.at(currentWin)->getOrigData()));
	_file.at(currentWin)->addFiltData(filter.dataToChar(tmp));
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_bernsen");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_bernsen");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::subsurfClicked() {
	if (dataTree->selectionModel()->selectedIndexes().size() == 0)
		errorMessages(0);
	else if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		if (indexOfVect == -1) indexOfVect = dataTree->currentIndex().row();
		_winParam.at(currentWin)->changeSubsurfParam(timeStepsSubsurf->value(), sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value());
		QVector<double> tmp;
		// bolo by vhodne prerobit 
		if (initialCBox->currentIndex() == 0) {
			if(gradTypeCBox->currentIndex() == 0)
				tmp = filter.subSurf(
					filter.distFunctSign(
							filter.dataToDouble(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()))),
					filter.changeRangeOfData(
						filter.dataToInt((_file.at(currentWin)->getFiltData(indexOfVect)))),
					timeStepsSubsurf->value() ,sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value(), true);
			else if (gradTypeCBox->currentIndex() == 1)
				tmp = filter.subSurf(
					filter.distFunctSign(
						filter.dataToDouble(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()))),
					filter.changeRangeOfData(
						filter.dataToInt(filter.dataDifference((_file.at(currentWin)->getFiltData(indexOfVect))))),
					timeStepsSubsurf->value(), sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value(), false);

		} else if (initialCBox->currentIndex() == 1) {
			if (gradTypeCBox->currentIndex() == 0)
				tmp = filter.subSurf(
					filter.thresholdFunction(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row())),
					filter.changeRangeOfData(
						filter.dataToInt(_file.at(currentWin)->getFiltData(indexOfVect))),
					timeStepsSubsurf->value(), sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value(), true);
			else if (gradTypeCBox->currentIndex() == 1)
				tmp = filter.subSurf(
					filter.thresholdFunction(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row())),
					filter.changeRangeOfData(
						filter.dataToInt(filter.dataDifference(_file.at(currentWin)->getFiltData(indexOfVect)))),
					timeStepsSubsurf->value(), sigmaSubsurf->value(), tauSubsurf->value(), kSubsurf->value(), false);
		}
		_file.at(currentWin)->add3DData(tmp);
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(_file.at(currentWin)->getSize3DData() - 1));
		_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
		QString txt = "SUBSURF PARAM ~ \nNumber of steps: " + QString::number(timeStepsSubsurf->value()) +
			"\nSize of linear time step: " + QString::number(sigmaSubsurf->value()) +
			"\nSize of nonlinear time step: " + QString::number(tauSubsurf->value()) +
			"\nSensitivity coeficient: " + QString::number(kSubsurf->value()) + "\n" +
			_file.at(currentWin)->getText();
		historyText->appendPlainText(txt);
		_vWidget.at(currentWin)->setViewerWidget3D(_file.at(currentWin)->getPolydata());
		txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
		addSubItem(parent3D, txt + "_subsurf");
		_winParam.at(currentWin)->add3DData(txt + "_subsurf");
		update3DWidget();
		indexOfVect = -1;
		ui->statusbar->clearMessage();
	}
	else 
		errorMessages(1);
}

void bioData::actionDistFunc() {
	QMessageBox mbox;
	if (dataTree->selectionModel()->selectedIndexes().size() == 0) 
		errorMessages(0);
	else if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		QVector<double> tmp = filter.distFunct(filter.boundary(filter.dataToDouble(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()))));
		_file.at(currentWin)->add3DData(tmp);
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(_file.at(currentWin)->getSize3DData() - 1));
		_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
		_vWidget.at(currentWin)->setViewerWidget3D(_file.at(currentWin)->getPolydata());
		QString txt = "DISTANCE FUNCTION ~" +
			_file.at(currentWin)->getText();
		historyText->appendPlainText(txt);
		txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
		addSubItem(parent3D, txt + "_dist_function");
		_winParam.at(currentWin)->add3DData(txt + "_dist_function");
		update3DWidget();
		ui->statusbar->clearMessage();
	}
	else 
		errorMessages(1);
}

void bioData::update3DWidget() {
	options3DDock->show();
	options2DDock->hide();
	threeDClicked();
	_winParam.at(currentWin)->addHistInfo(historyText->toPlainText());
}

void bioData::update2DWidget() {
	_vWidget.at(currentWin)->updateViewerWidget2D();
	options2DDock->show();
	options3DDock->hide();
	twoDClicked();
	_winParam.at(currentWin)->addHistInfo(historyText->toPlainText());
}

void bioData::actionSignDistFunc() {
	if (dataTree->selectionModel()->selectedIndexes().size() == 0) 
		errorMessages(0);
	if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		QVector<double> tmp = filter.distFunctSign(filter.dataToDouble(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row())));
		_file.at(currentWin)->add3DData(tmp);
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(_file.at(currentWin)->getSize3DData() - 1));
		_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
		_vWidget.at(currentWin)->setViewerWidget3D(_file.at(currentWin)->getPolydata());
		QString txt = "DISTANCE SIGN  FUNCTION PARAM ~ \nNumber of steps: \n" +
			_file.at(currentWin)->getText();
		historyText->appendPlainText(txt);
		txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
		addSubItem(parent3D, txt + "_sign_dist_function");
		_winParam.at(currentWin)->add3DData(txt + "_sign_dist_function");
		update3DWidget();
		ui->statusbar->clearMessage();
	}
	else
		errorMessages(1);
}

void bioData::createSubsurfGB() {
	subsurfGroupBox = new QGroupBox(tr("SUBSURF"));

	QGridLayout *subsurfLayout = new QGridLayout;
	QLabel *sigmaLabel = new QLabel(tr("Size of (linear) time steps:"));
	QLabel *tauLabel = new QLabel(tr("Size of (non-linear) time steps:"));
	QLabel *kLabel = new QLabel(tr("Sensitivity coeficient:"));
	//QLabel *initConLabel = new QLabel(tr("Initial condition:"));
	QLabel *howManyLab = new QLabel(tr("Number of time steps:"));
	//QLabel *improveLab = new QLabel(tr("Improve vector field: "));

	initialCBox->setToolTip("Initial condition");
	initialCBox->addItems(QStringList() << "Sign distance function"  << "Result of threshold function");
	gradTypeCBox->setToolTip("Choose gratient type");
	gradTypeCBox->addItems(QStringList() << "grad1" << "grad2");

	// subsurfLayout->addWidget(initConLabel, 0, 0);
	subsurfLayout->addWidget(howManyLab, 1, 0);
	subsurfLayout->addWidget(timeStepsSubsurf, 1, 1);
	subsurfLayout->addWidget(sigmaLabel, 2, 0);
	subsurfLayout->addWidget(sigmaSubsurf, 2, 1);
	subsurfLayout->addWidget(tauLabel, 3, 0);
	subsurfLayout->addWidget(tauSubsurf, 3, 1);
	subsurfLayout->addWidget(kLabel, 4, 0);
	subsurfLayout->addWidget(kSubsurf, 4, 1);
	subsurfLayout->addWidget(gradTypeCBox, 5, 0);
	zlepsiVectorFieldButton->setText("Apply");
	subsurfLayout->addWidget(zlepsiVectorFieldButton, 5, 1);
	subsurfLayout->addWidget(initialCBox, 6, 0);
	subsurfButton->setText("Apply");
	subsurfLayout->addWidget(subsurfButton, 6, 1);

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
	qApp->processEvents();
	if (dataTree->selectedItems().size() == 0) {
		errorMessages(0);
		return;
	}
	int i = dataTree->currentIndex().row();
	if (dataTree->topLevelItemCount() == 1 && parent2D->childCount() == 1) {
		dataTree->model()->removeRow(i);
		actionClose();
	}
	else if (parent3D == dataTree->currentItem()->parent()) {
		if (parent3D->childCount() == 1) {
			parent3D->removeChild(parent3D->child(i));
			_file.at(currentWin)->remove3DFiltData(i);
			dataTree->setCurrentItem(parent3D->child(i - 1));
			parent3D->setHidden(true);
			dataTree->setCurrentItem(parent2D->child(parent2D->childCount() - 1));
			_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()));
			_vWidget.at(currentWin)->updateViewerWidget2D();
			twoDClicked();
		}
		else {
			parent3D->removeChild(parent3D->child(i));
			_file.at(currentWin)->remove3DFiltData(i);
			if (i =! 0)
				dataTree->setCurrentItem(parent3D->child(i - 1));
			else 
				dataTree->setCurrentItem(parent3D->child(i + 1));
			_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
			_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
		}
	}
	else if (parent2D == dataTree->currentItem()->parent()) {
		if (dataTree->currentIndex().row() == 0 && parent3D->childCount() == 0 && parent2D->childCount() == 1) {
			if (winListView->count() == 1)
				actionCloseFiles();
			else
				deleteWinClicked();
		}
		else if (dataTree->currentIndex().row() == 0) {
			errorMessages(4);
		}
		else {
			parent2D->removeChild(parent2D->child(i));
			_file.at(currentWin)->remove2DFiltData(i);
			dataTree->setCurrentItem(parent2D->child(i - 1));
			_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()));
			_vWidget.at(currentWin)->updateViewerWidget2D();
		}
	}
}

void bioData::resetViewClicked () {
	_vWidget.at(currentWin)->resetCam();
}

void bioData::actionCloseFiles() {
	qApp->processEvents();

	if (mdiArea->subWindowList().length() > 0) {
		_file.clear();
		_winParam.clear();
		_vWidget.clear();
		_subW.clear();
		winListView->clear();
		mdiArea->closeAllSubWindows();
		dataTree->clear();
		winListView->clear();
		hideAllDocks();
		disableMenuOpt();
	}
	else {
		errorMessages(3);
	}
}

void bioData::twoDClicked() {
	twoDButton->setChecked(true);
	threeDButton->setChecked(false);
	_vWidget.at(currentWin)->set2DView();
	resetViewClicked();
}

void bioData::threeDClicked() {
	threeDButton->setChecked(true);
	twoDButton->setChecked(false);
	_vWidget.at(currentWin)->set3DView();
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

	QGroupBox *hybNBaBrenGBox = new QGroupBox(tr("Hybrid of Niblack's and Bernsen's methods"));
	QGridLayout *subNBLayout = new QGridLayout;
	QLabel *timeStepLab1 = new QLabel(tr("Time step size:"));
	QLabel *niblackMaskLabel1 = new QLabel(tr("Mask size:"));
	hybNBABernButton->setText("Apply");
	subNBLayout->addWidget(timeStepLab1, 1, 0);
	subNBLayout->addWidget(NBaBrenTimeStepSB, 1, 1);
	subNBLayout->addWidget(niblackMaskLabel1, 2, 0);
	subNBLayout->addWidget(NBaBrenMaskSB, 2, 1);
	subNBLayout->addWidget(hybNBABernButton, 3, 1);
	hybNBaBrenGBox->setLayout(subNBLayout);

	QGroupBox *sauvolaGBox = new QGroupBox(tr("Sauvola's  method"));
	QGridLayout *subSLayout = new QGridLayout;
	QLabel *timeStepLab2 = new QLabel(tr("Time step size:"));
	QLabel *sauvolaMaskLabel = new QLabel(tr("Mask size:"));
	sauvolaButton->setText("Apply");
	subSLayout->addWidget(timeStepLab2, 1, 0);
	subSLayout->addWidget(sauvolaTimeStepSB, 1, 1);
	subSLayout->addWidget(sauvolaMaskLabel, 2, 0);
	subSLayout->addWidget(sauvolaMaskSB, 2, 1);
	subSLayout->addWidget(sauvolaButton, 3, 1);
	sauvolaGBox->setLayout(subSLayout);

	QGroupBox *hybSaBrenGBox = new QGroupBox(tr("Hybrid of Sauvola's and Bernsen's methods"));
	QGridLayout *subhSBLayout = new QGridLayout;
	QLabel *timeStepLab3 = new QLabel(tr("Time step size:"));
	QLabel *Lab = new QLabel(tr("Mask size:"));
	hybSaBernButton->setText("Apply");
	subhSBLayout->addWidget(timeStepLab3, 1, 0);
	subhSBLayout->addWidget(SaBrenTimeStepSB, 1, 1);
	subhSBLayout->addWidget(Lab, 2, 0);
	subhSBLayout->addWidget(SaBrenMaskSB, 2, 1);
	subhSBLayout->addWidget(hybSaBernButton, 3, 1);
	hybSaBrenGBox->setLayout(subhSBLayout);

	layout->addWidget(niblackGBox);
	layout->addWidget(bernsenGBox);
	layout->addWidget(hybNBaBrenGBox);
	layout->addWidget(sauvolaGBox);
	layout->addWidget(hybSaBrenGBox);
	locThreshGroupBox->setLayout(layout);
}

void bioData::setDefaultValues() {
	// subsurf param
	timeStepsSubsurf->setRange(1, 200);
	timeStepsSubsurf->setValue(10);
	sigmaSubsurf->setRange(0.0001, 1000.0);
	sigmaSubsurf->setDecimals(3);
	sigmaSubsurf->setSingleStep(0.1);
	sigmaSubsurf->setValue(0.25);
	tauSubsurf->setRange(0.0001, 1000.0);
	tauSubsurf->setDecimals(3);
	tauSubsurf->setSingleStep(0.1);
	tauSubsurf->setValue(1.0);
	kSubsurf->setRange(0.00001, 999999.0);
	kSubsurf->setDecimals(2);
	kSubsurf->setSingleStep(0.5);
	kSubsurf->setValue(100);

	// niblack param
	niblackTimeStepSB->setRange(0.0001, 1000.0);
	niblackTimeStepSB->setDecimals(5);
	niblackTimeStepSB->setSingleStep(0.1);
	niblackTimeStepSB->setValue(5.0);
	niblackMaskSB->setRange(1, 50);
	niblackMaskSB->setValue(3);
	
	// bernsen param
	bernsenMaskSB->setRange(1, 50);
	bernsenMaskSB->setValue(2);

	// sauvola 
	sauvolaTimeStepSB->setRange(0.0001, 1000.0);
	sauvolaTimeStepSB->setDecimals(5);
	sauvolaTimeStepSB->setSingleStep(0.1);
	sauvolaTimeStepSB->setValue(5.0);
	sauvolaMaskSB->setRange(1, 50);
	sauvolaMaskSB->setValue(3);

	// hybrid nbb
	NBaBrenTimeStepSB->setRange(0.0001, 1000.0);
	NBaBrenTimeStepSB->setDecimals(5);
	NBaBrenTimeStepSB->setSingleStep(0.1);
	NBaBrenTimeStepSB->setValue(5.0);
	NBaBrenMaskSB->setRange(1, 50);
	NBaBrenMaskSB->setValue(3);

	// hybrid sbb
	SaBrenTimeStepSB->setRange(0.0001, 1000.0);
	SaBrenTimeStepSB->setDecimals(5);
	SaBrenTimeStepSB->setSingleStep(0.1);
	SaBrenTimeStepSB->setValue(5.0);
	SaBrenMaskSB->setRange(1, 50);
	SaBrenMaskSB->setValue(3);

	//contours 
	numCont3DSB->setRange(1, 1000);
	numCont3DSB->setValue(10);

	//contour val
	contourZConSB->setRange(-100, 100);
	contourZConSB->setValue(-1);

	// heatEq
	heatEqSB->setRange(0.0001, 1000.0);
	heatEqSB->setDecimals(3);
	heatEqSB->setSingleStep(0.1);
	heatEqSB->setValue(1.0);

	// cut at
	cutDataAtSB->setRange(-100, 100);
	cutDataAtSB->setValue(-8);
}

void bioData::thresholdInitConClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		QVector<double> tmp = filter.thresholdFunction(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()));
		_file.at(currentWin)->add3DData(tmp);
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(_file.at(currentWin)->getSize3DData() - 1));
		_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
		_vWidget.at(currentWin)->setViewerWidget3D(_file.at(currentWin)->getPolydata());
		QString txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
		addSubItem(parent3D, txt + "_threshold_function");
		_winParam.at(currentWin)->add3DData(txt + "_threshold_function");
		update3DWidget();
		ui->statusbar->clearMessage();
	}
	else
		errorMessages(1);
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
	QLabel *differenceLab = new QLabel(tr("Aritmetic mean: "));
	QLabel *useODataLab = new QLabel(tr("Use original data: "));
	QLabel *heLab = new QLabel(tr("One step of Heat Equation:"));
	QLabel *originalDataLab = new QLabel(tr("Process original data:"));
	differenceLab->setToolTip("Creates new boundary condition for the segmentation.\n Takes 1/2 of the selected thresholded data and 1/2 and makes mean.");
	differenceButton->setText("Apply");
	createcontour2DGB();
	createHeatEqGB();
	useOData->setToolTip("Means using first data in list.");
	useOData->setChecked(true);
	//layout->addWidget(useODataLab, 0, 0);
	//layout->addWidget(useOData, 0, 1);
	layout->addWidget(differenceLab, 1, 0);
	layout->addWidget(differenceButton, 1, 1);
	layout->addWidget(HeatEqGroupBox, 2, 0, 1, 2);
	layout->addWidget(contour2DGroupBox, 3, 0, 1, 2);
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
	colorCBox->addItems(QStringList() << "Black & White" << "Rainbow");

	createCutDataAtGB();
	createcontour3DGB();
	//createtestGB();
	createrManOptContourGB();
	layout->addWidget(AxesLab,0, 0);
	layout->addWidget(axesCB, 0, 1);
	layout->addWidget(colorLab, 1, 0);
	layout->addWidget(colorCBox, 1, 1);
	layout->addWidget(cutDataAtGB, 2, 0, 1, 2);
	layout->addWidget(contour3DGroupBox,3,0,1,2);
	layout->addWidget(manOptContourGB, 4, 0, 1, 2);
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
	histSaveButton->setText("SAVE HISTORY LOG");
	historyText->setReadOnly(true);
	layout->addWidget(historyText);
	layout->addWidget(histSaveButton);
	multiWidget->setLayout(layout);
	historyDock->setWidget(multiWidget);

	addDockWidget(Qt::RightDockWidgetArea, historyDock);
}

void bioData::contour3DClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->contours3D(_file.at(currentWin)->getPolydata(), numCont3DSB->value(), false);
		_subW.at(currentWin)->update();
		ui->statusbar->clearMessage();
	}
	else
		errorMessages(2);
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
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->contours2D(_file.at(currentWin)->getImageData(), false);
		dataTree->selectionModel()->clearSelection();
		ui->statusbar->clearMessage();
	} else 
		errorMessages(1);
}

void bioData::contour2DwIDClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->contours2D(_file.at(currentWin)->getImageData());
		dataTree->selectionModel()->clearSelection();
		ui->statusbar->clearMessage();
	} else 
		errorMessages(1);
}

void bioData::contour3DwDClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->contours3D(_file.at(currentWin)->getPolydata(), numCont3DSB->value());
		dataTree->selectionModel()->clearSelection();
		_subW.at(currentWin)->update();
		ui->statusbar->clearMessage();
	}
	else
		errorMessages(2);
}

void bioData::differenceClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_file.at(currentWin)->addFiltData(filter.dataDifference(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row())));
		_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
		addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_aritmetic_mean");
		_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_aritmetic_mean");
		update2DWidget();
		ui->statusbar->clearMessage();
	}
	else 
		errorMessages(1);
}
 
void bioData::heatEquationClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_winParam.at(currentWin)->changeheatEqParam(heatEqSB->value());
		_file.at(currentWin)->addFiltData(filter.dataToChar(filter.antireflection(filter.heatImpl(filter.dataToDouble(_file.at(currentWin)->getFiltData(dataTree->currentIndex().row())), heatEqSB->value()))));
		_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
		addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_heatEq");
		_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_heatEq");
		update2DWidget();
		ui->statusbar->clearMessage();
	}
	else 
		errorMessages(1);
}

void bioData::AxesChange(bool checked) {
	if (parent3D == dataTree->currentItem()->parent()) 
		if (checked) {
			filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
			_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
			_vWidget.at(currentWin)->addAxes(_file.at(currentWin)->getPolydata());
			_subW.at(currentWin)->update();
		}
		else {
			_vWidget.at(currentWin)->removeAxes();
			_subW.at(currentWin)->update();
		}
	else
		errorMessages(0);
}

void bioData::colorIndexChanged(int i) {
	if (parent3D != nullptr)
		if( parent3D == dataTree->currentItem()->parent()) {
			_file.at(currentWin)->colorPolyData(i);
			_vWidget.at(currentWin)->updateViewerWidget3D();
		}
}

void bioData::contour3DPClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_winParam.at(currentWin)->changeNumberOfCont3D(numCont3DSB->value());
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->cutContour(_file.at(currentWin)->getPolydata(), numCont3DSB->value(), false);
		dataTree->selectionModel()->clearSelection();
		_subW.at(currentWin)->update();
	}
	else
		errorMessages(2);
}

void bioData::contour3DPwDClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_winParam.at(currentWin)->changeNumberOfCont3D(numCont3DSB->value());
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->cutContour(_file.at(currentWin)->getPolydata(), numCont3DSB->value());
		dataTree->selectionModel()->clearSelection();
		_subW.at(currentWin)->update();
	} 
	else
		errorMessages(2);
}

void bioData::testClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(_file.size() - 1)->getWidth(), _file.at(_file.size() - 1)->getHeight(), _file.at(_file.size() - 1)->getOrigData(), 80);
	//QVector<unsigned char> tmp = filter.dataToChar(filter.sauvolaThreshold(filter.changeRangeOfData(filter.dataToInt(_file.at(_file.size() - 1)->getOrigData())), niblackTimeStepSB->value()));
	QVector<double> tmp = filter.reflection(filter.dataToDouble(_file.at(_file.size() - 1)->getOrigData()));
	//_file.at(_file.size() - 1)->addFiltData(tmp);
	//_file.at(_file.size() - 1)->setPoints(_file.at(_file.size() - 1)->getFiltData(_file.at(_file.size() - 1)->getSizeFiltData() - 1));
	//update2DWidget();
	//addSubItem(parent2D, fName + "_test");
	ui->statusbar->clearMessage();
}

void bioData::createrManOptContourGB() {
	manOptContourGB = new QGroupBox(tr("Find optimal contour (manually)"));
	QGridLayout *layout = new QGridLayout;
	QLabel *zLab = new QLabel(tr("Z coordinate of contour: "));
	QLabel *ogDataLab = new QLabel(tr("Display on original data: "));
	manOptContourButton->setText("Show");
	optContDispButton->setText("Show");
	layout->addWidget(zLab, 0, 0);
	layout->addWidget(contourZConSB, 0, 1);
	layout->addWidget(manOptContourButton, 1, 1);
	layout->addWidget(ogDataLab, 2, 0);
	layout->addWidget(optContDispButton, 2, 1);

	manOptContourGB->setLayout(layout);
}

void bioData::manOptContClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_winParam.at(currentWin)->changeZValOfCont3D(contourZConSB->value());
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->cut1Contour(_file.at(currentWin)->getPolydata(), contourZConSB->value());
		_subW.at(currentWin)->update();
	}
	else
		errorMessages(2);
}

void bioData::optContDispClicked() {
	if (parent3D == dataTree->currentItem()->parent()) {
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_winParam.at(currentWin)->changeZValOfCont3D(contourZConSB->value());
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()));
		_vWidget.at(currentWin)->cut1Contour(_file.at(currentWin)->getPolydata(), contourZConSB->value(), true);
		_file.at(currentWin)->setPoints(_file.at(currentWin)->getOrigData());
		_vWidget.at(currentWin)->optContourOnID(contourZConSB->value());
		dataTree->selectionModel()->clearSelection();
		twoDClicked();
	}
	else
		errorMessages(2);
}

void bioData::histSavedClicked() {
	QString fname= QFileDialog::getSaveFileName(this, tr("Save File"),
		"history_log.txt",
		tr("Text File (*.txt)"));
	if (fname.isEmpty())
		return;
	_file.at(currentWin)->saveHistOutput(historyText->toPlainText(), fname);
}  

void bioData::showAllDocks() {
	listDock->show();
	filter2DDock->show();
	subsurfDock->show();
	historyDock->show();
	if (parent2D == dataTree->currentItem()->parent())
		options2DDock->show();
	else if (parent3D == dataTree->currentItem()->parent())
		options3DDock->show();
	this->ui->actionFileInfo->setChecked(true);
	this->ui->actionData->setChecked(true);
	this->ui->action2DFilters->setChecked(true);
	this->ui->action3DFilters->setChecked(true);
	this->ui->actionHistory->setChecked(true);
}

void bioData::hideAllDocks() {
	listDock->hide();
	filter2DDock->hide();
	subsurfDock->hide();
	historyDock->hide();
	options2DDock->hide();
	options3DDock->hide();
	windowsDock->hide();
	this->ui->actionFileInfo->setChecked(false);
	this->ui->actionData->setChecked(false);
	this->ui->action2DFilters->setChecked(false);
	this->ui->action3DFilters->setChecked(false);
	this->ui->actionHistory->setChecked(false);
}

void bioData::disableMenuOpt() {
	this->ui->menuTabs->setDisabled(true);
	this->ui->menuSave->setDisabled(true);
	this->ui->actionClose_Files->setDisabled(true);
}

void bioData::enableMenuOpt() {
	this->ui->menuTabs->setDisabled(false);
	this->ui->menuSave->setDisabled(false);
	this->ui->actionClose_Files->setDisabled(false);
}

void bioData::cutDataAtClicked() { 
	if (dataTree->selectionModel()->selectedIndexes().size() == 0) 
		errorMessages(0);
	if (parent3D == dataTree->currentItem()->parent()) {
		ui->statusbar->showMessage("Computing...");
		qApp->processEvents();
		filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData());
		_winParam.at(currentWin)->changecutDataAtVal(cutDataAtSB->value());
		QVector<double> tmp = filter.cutDataAt(_file.at(currentWin)->get3DData(dataTree->currentIndex().row()), cutDataAtSB->value()); // treba opravit
		_file.at(currentWin)->add3DData(tmp);
		_file.at(currentWin)->create3Ddata(_file.at(currentWin)->get3DData(_file.at(currentWin)->getSize3DData() - 1));
		_file.at(currentWin)->colorPolyData(colorCBox->currentIndex());
		_vWidget.at(currentWin)->setViewerWidget3D(_file.at(currentWin)->getPolydata());
		update3DWidget();
		QString txt = dataTree->currentItem()->text(dataTree->currentIndex().column());
		addSubItem(parent3D, txt + "cut_data_at" + QString::number(cutDataAtSB->value()));
		_winParam.at(currentWin)->add3DData(txt + "cut_data_at" + QString::number(cutDataAtSB->value()));
		_winParam.at(currentWin)->addHistInfo(historyText->toPlainText());
		ui->statusbar->clearMessage();
	}
	else 
		errorMessages(2);
}

void bioData::createCutDataAtGB() {
	cutDataAtGB = new QGroupBox;
	QGridLayout *layout = new QGridLayout;
	QLabel *lab = new QLabel(tr("Cut data at: "));

	cutDataAtButton->setText("Apply");
	layout->addWidget(lab, 0, 0);
	layout->addWidget(cutDataAtSB, 0, 1);
	layout->addWidget(cutDataAtButton, 1, 1);

	cutDataAtGB->setLayout(layout);
}

void bioData::hybNBABernClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData(), NBaBrenMaskSB->value());
	_winParam.at(currentWin)->changeSauvolaParam(NBaBrenTimeStepSB->value(), NBaBrenMaskSB->value());
	QVector<unsigned char> tmp = filter.dataToChar(filter.hybBernsenAndNiblack(filter.changeRangeOfData(filter.dataToInt(_file.at(currentWin)->getOrigData())), NBaBrenTimeStepSB->value()));
	_file.at(currentWin)->addFiltData(tmp);
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_hybrid_nb");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_hybrid_nb");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::sauvolaClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData(), sauvolaMaskSB->value());
	_winParam.at(currentWin)->changeSauvolaParam(sauvolaTimeStepSB->value(), sauvolaMaskSB->value());
	QVector<unsigned char> tmp = filter.dataToChar(filter.sauvolaThreshold(filter.changeRangeOfData(filter.dataToInt(_file.at(currentWin)->getOrigData())), sauvolaTimeStepSB->value()));
	_file.at(currentWin)->addFiltData(tmp);
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_sauvola");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_sauvola");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::hybSaBernClicked() {
	ui->statusbar->showMessage("Computing...");
	qApp->processEvents();
	filters filter(_file.at(currentWin)->getWidth(), _file.at(currentWin)->getHeight(), _file.at(currentWin)->getOrigData(), SaBrenMaskSB->value());
	QVector<unsigned char> tmp = filter.dataToChar(filter.hybBernsenAndSauvola(filter.changeRangeOfData(filter.dataToInt(_file.at(currentWin)->getOrigData())), SaBrenTimeStepSB->value()));
	_file.at(currentWin)->addFiltData(tmp);
	_file.at(currentWin)->setPoints(_file.at(currentWin)->getFiltData(_file.at(currentWin)->getSizeFiltData() - 1));
	addSubItem(parent2D, _winParam.at(currentWin)->getFileName() + "_hybrid_sb");
	_winParam.at(currentWin)->add2DData(_winParam.at(currentWin)->getFileName() + "_hybrid_sb");
	update2DWidget();
	ui->statusbar->clearMessage();
}

void bioData::listIndexChanged(int i) {
	currentWin = i;
	if (currentWin == -1)
		return;
	else if (subWinAdded) {
		subWinAdded = false;
		return;
	}
	else { 
		filter2DDock->raise();

		initialCBox->setCurrentIndex(0);
		colorCBox->setCurrentIndex(0);

		timeStepsSubsurf->setValue(_winParam.at(currentWin)->getHowManySubsurf());  //subsurf
		sigmaSubsurf->setValue(_winParam.at(currentWin)->getSigmaSubsurf()); 
		tauSubsurf->setValue(_winParam.at(currentWin)->getTauSubsurf());
		kSubsurf->setValue(_winParam.at(currentWin)->getKSubsurf());

		niblackTimeStepSB->setValue(_winParam.at(currentWin)->getNBTimeStep()); // niblack
		niblackMaskSB->setValue(_winParam.at(currentWin)->getNBMask());

		bernsenMaskSB->setValue(_winParam.at(currentWin)->getBernsenMask()); // bernsen
		sauvolaTimeStepSB->setValue(_winParam.at(currentWin)->getSTimeStep()); // sauvola
		sauvolaMaskSB->setValue(_winParam.at(currentWin)->getSMask());
		NBaBrenTimeStepSB->setValue(_winParam.at(currentWin)->getHybNBBTimeStep()); // niblack a Bren
		NBaBrenMaskSB->setValue(_winParam.at(currentWin)->getHybNBBMask());
		SaBrenTimeStepSB->setValue(_winParam.at(currentWin)->getHybSBTimeStep()); // sauvola a Bren
		SaBrenMaskSB->setValue(_winParam.at(currentWin)->getHybSBMask());
		contourZConSB->setValue(_winParam.at(currentWin)->getcontourZCon());
		cutDataAtSB->setValue(_winParam.at(currentWin)->getcutDataAt());
		numCont3DSB->setValue(_winParam.at(currentWin)->getnumCont3D());
		heatEqSB->setValue(_winParam.at(currentWin)->getheatEqTS());

		historyText->clear();
		historyText->setPlainText(_winParam.at(currentWin)->getHistText());
		_subW.at(currentWin)->setWindowTitle(_winParam.at(currentWin)->getFileName());
		dataTree->clear();
		parent2D = new QTreeWidgetItem();
		parent2D->setText(0, "2D");
		parent3D = new QTreeWidgetItem();
		parent3D->setText(0, "3D");
		dataTree->addTopLevelItem(parent2D);
		dataTree->addTopLevelItem(parent3D);
		
		for (int i = 0; i < _file.at(currentWin)->getSizeFiltData(); i++) {
			addSubItem(parent2D, _winParam.at(currentWin)->get2DDataItem(i));
		}
		if (_file.at(currentWin)->getSize3DData() == 0) {
			parent3D->setHidden(true);
		}
		else {
			for (int i = 0; i < _file.at(currentWin)->getSize3DData(); i++) {
				addSubItem(parent3D, _winParam.at(currentWin)->get3DDataItem(i));
			}
		}
		_subW.at(currentWin)->update();
		_subW.at(currentWin)->raise();
		_subW.at(currentWin)->showMaximized();
		subWinAdded = false;
	}
}

void bioData::createWindowsDock() {
	windowsDock = new QDockWidget(tr("Opened Windows"), this);
	windowsDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	windowsDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable |
		QDockWidget::DockWidgetVerticalTitleBar);
	QWidget* multiWidget = new QWidget();
	QGridLayout *layout = new QGridLayout;
	deleteWinButton->setText("CLOSE CURRENT WINDOW");
	layout->addWidget(winListView);
	layout->addWidget(deleteWinButton);
	multiWidget->setLayout(layout);
	windowsDock->setWidget(multiWidget);
	addDockWidget(Qt::RightDockWidgetArea, windowsDock);
}

void bioData::deleteWinClicked() {
	if (_subW.size() > 1) {
		if (_subW.size() == 2)
			windowsDock->hide();
		_file.remove(currentWin);
		_winParam.remove(currentWin);
		_vWidget.remove(currentWin);
		_subW.at(currentWin)->close();
		_subW.remove(currentWin);
		winListView->model()->removeRow(currentWin);
		if (currentWin == 0) {
			winListView->setCurrentRow(currentWin + 1);
			currentWin = currentWin + 1;
		}
		else {
			winListView->setCurrentRow(currentWin - 1);
			currentWin = currentWin - 1;
		}
	}
	else if (_subW.size() == 1) {
		actionCloseFiles();
	}
}

void bioData::actionHelp() {
	helpDock->show();
	helpDock->raise();
}

void bioData::actionAbout() {
	QMessageBox aboutBox;
	aboutBox.setWindowTitle("About");

	QString about = "KMaDG\n";
	about += "Version:  1.0   (2020) \n\n";
	about += "Author: Maria Somorovska";

	aboutBox.setText(about);
	aboutBox.exec();
}

void bioData::errorMessages(int i) {
	QMessageBox errorMessage;
	switch (i) {
	case 0:
		errorMessage.setText("No data selected!");
		break;
	case 1:
		errorMessage.setText("2D data must be selected!");
		break;
	case 2:
		errorMessage.setText("3D data must be selected!");
		break;
	case 3:
		errorMessage.setText("Something went wrong!");
		break;
	case 4:
		errorMessage.setText("You can't delete original data while having more items in the list!");
		break;
	case 5:
		errorMessage.setText("Wrong file type choosen!");
		break;
	}
	errorMessage.exec();
}

void bioData::createHelpDock() {
	helpDock = new QDockWidget(tr("Help"), this);
	helpDock->setAllowedAreas(Qt::LeftDockWidgetArea |
		Qt::RightDockWidgetArea |
		Qt::BottomDockWidgetArea);
	helpDock->setFeatures(QDockWidget::DockWidgetClosable |
		QDockWidget::DockWidgetMovable);

	QDir tmpCurrDir = QDir::current();
	tmpCurrDir.cdUp();
	QString rootDir = tmpCurrDir.path();
	
	QHelpEngine* helpEngine = new QHelpEngine(
		rootDir + "/src/documentation/biodataHelp.qhc");
	helpEngine->setupData();

	QTabWidget* tWidget = new QTabWidget;
	tWidget->setMaximumWidth(150);
	tWidget->addTab(helpEngine->contentWidget(), "Contents");

	Help *textViewer = new Help(helpEngine);
	 textViewer->setSource(
	 	QUrl("qthelp://biodata.qt.help/doc/index.html"));

	 connect(helpEngine->contentWidget(),
		 SIGNAL(linkActivated(QUrl)),
		 textViewer, SLOT(setSource(QUrl)));

	QSplitter *horizSplitter = new QSplitter(Qt::Horizontal);
	horizSplitter->insertWidget(0, tWidget);
	horizSplitter->insertWidget(1, textViewer);
	horizSplitter->hide();

	helpDock->setWidget(horizSplitter);
	helpDock->hide();
	addDockWidget(Qt::BottomDockWidgetArea, helpDock);
}

void bioData::zlepsiVectorFieldClicked() {
	if (parent2D == dataTree->currentItem()->parent()) {
		indexOfVect = dataTree->currentIndex().row();
	}
	else
		errorMessages(1);
}

void bioData::openWinClicked() {
	return;
	/*if (parent2D == dataTree->currentItem()->parent()) {
		fName = dataTree->currentItem()->text(dataTree->currentColumn());
		int i = dataTree->currentIndex().row();

		source *tmpFile = new source();
		_file.resize(_file.size() + 1);
		_file.replace(_file.size() - 1, tmpFile);

		viewerWidget *VWTmp = new viewerWidget();
		_vWidget.resize(_vWidget.size() + 1);
		_vWidget.replace(_vWidget.size() - 1, VWTmp);
		_vWidget.at(_vWidget.size() - 1)->setScrollArea();

		historyText->clear();
		historyText->appendPlainText("Data opened in new window.");
		historyText->appendPlainText("File name: " + fName);
		historyText->appendPlainText("File path: unknown");
		historyText->appendPlainText("Width: " + QString::number(tmpFile->getWidth()) + " Height: " + QString::number(tmpFile->getHeight()));

		QMdiSubWindow *subWTmp = new QMdiSubWindow();
		_subW.resize(_subW.size() + 1);
		QWidget *widget = new QWidget();
		gridLayout = new QGridLayout(widget);
		dataTree->clear();
		parent2D = new QTreeWidgetItem();
		parent2D->setText(0, "2D");
		parent3D = new QTreeWidgetItem();
		parent3D->setText(0, "3D");
		dataTree->addTopLevelItem(parent2D);
		dataTree->addTopLevelItem(parent3D);
		parent3D->setHidden(true);
		_subW.replace(_subW.size() - 1, mdiArea->addSubWindow(widget));
		options3DDock->hide();
		options2DDock->hide();
		setDefaultValues();
		twoDButton->setChecked(true);
		_file.at(_file.size() - 1)->setPoints(_file.at(currentWin)->getFiltData(i));
		gridLayout->addWidget(_vWidget.at(_vWidget.size() - 1)->getScrollArea());
		_vWidget.at(_vWidget.size() - 1)->setViewerWidget2D(tmpFile->getImageData(), tmpFile->getFileName(fName));

		enableMenuOpt();
		subWin *winTmp = new subWin(fName);
		_winParam.resize(_winParam.size() + 1);
		_winParam.replace(_winParam.size() - 1, winTmp);
		_winParam.at(_winParam.size() - 1)->add2DData(fName);
		_winParam.at(_winParam.size() - 1)->addHistInfo(historyText->toPlainText());
		winListView->addItem(fName);
		subWinAdded = true;
		winListView->setCurrentRow(winListView->count() - 1);
		_subW.at(currentWin)->setWindowTitle(fName);
		addSubItem(parent2D, fName);
		if (winListView->count() == 1)
			windowsDock->hide();
		else
			windowsDock->show();
		filter2DDock->raise();
		_subW.at(currentWin)->showMaximized();
		// _subW.at(currentWin)->setDisabled(true);
	}
	else
		errorMessages(1);*/
}