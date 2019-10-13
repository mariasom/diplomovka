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
	//grdSource *fTmp = static_cast<grdSource*>(_file);
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
	w->setViewerWidget(fTmp->getData(), fTmp->getFileName(fName));
	visualize();
}

/*void bioData::actionOpenFile()
{
	_vViewerWidget->setScrollArea();
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Portable Graymap (*.pgm)"));
	_vData->load(fileName);
	//_vViewerWidget->setViewerWidget();
	//_vData->setPoints();
	//_vViewerWidget->setViewerWidget();

	//QGridLayout* gridLayout = new QGridLayout;

	//gridLayout->addWidget(_vViewerWidget->getScrollArea());

	// cout << fileName.toStdString() << endl;
	// QFile inputFile(fileName);
	// inputFile.open(QIODevice::ReadOnly);
	// if (!inputFile.isOpen())
	// {
	//	return;
	// }
	// p2
	// QString wholeFile = inputFile.readAll();
	// cout << wholeFile.toStdString();
	// width & height
	/*QString line = inputFile.readLine();
	// cout << line.toStdString();
	QStringList prop = line.split(' ');
	// cout << prop.length();
	int width = prop[1].toInt();
	int heigth = prop[2].toInt();
	QString col = inputFile.readLine();
	int colMax = col.toInt();

	QStringList split;
	for (int i = 0; i < width; i++) {
		line = inputFile.readLine();
		split = line.split(' ', QString::SkipEmptyParts);
		for (int j = 0; j < width; j++) {
			//cout << split[j].toInt() << " ";
		}
		//cout << endl;
	}*/

// }

void bioData::actionClose()
{
	// vymaze aktualny tab			DOROBIT: dealokaciu seckiho co bolo v tom tabe
	if (_index >= 0)
	{
		_index = _tabs->currentIndex();
		_tabs->removeTab(_index);
	}
}

/*void bioData::scaleClicked()
{
	QMessageBox mbox;
	mbox.setText("Scale factor: " + QString::number(scaleSpinBox_z->value()));
	mbox.exec();

	fTmp->scale(scaleSpinBox_z->value());
	visualize();
}*/

/*void bioData::colorClicked()
{
	QMessageBox mbox;
	mbox.setText("Index zvolenej palety: " + QString::number(colorComboBox->currentIndex())); //pripomienka! -> indexy prvkov ComboBoxu su pravdaze cislovane od 0
	mbox.exec();
}

void bioData::createScaleGroupBox()
{
	scaleGroupBox = new QGroupBox(tr("Scale"));

	//vytvorenie spin boxov a zadanie ich zakladnych vlastnosti
	QLabel *Label_x = new QLabel(tr("x"));
	Label_x->setAlignment(Qt::AlignHCenter);
	scaleSpinBox_x = new QDoubleSpinBox;
	scaleSpinBox_x->setRange(-100.0, 100.0);
	scaleSpinBox_x->setSingleStep(1.0);
	scaleSpinBox_x->setValue(1.0);

	QLabel *Label_y = new QLabel(tr("y"));
	Label_y->setAlignment(Qt::AlignHCenter);
	scaleSpinBox_y = new QDoubleSpinBox;
	scaleSpinBox_y->setRange(-100.0, 100.0);
	scaleSpinBox_y->setSingleStep(1.0);
	scaleSpinBox_y->setValue(1.0);

	QLabel *Label_z = new QLabel(tr("z"));
	Label_z->setAlignment(Qt::AlignHCenter);
	scaleSpinBox_z = new QDoubleSpinBox;
	scaleSpinBox_z->setRange(-100.0, 100.0);
	scaleSpinBox_z->setSingleStep(1.0);
	scaleSpinBox_z->setValue(10.0);

	//vytvorim button na spustenie skalovania
	scalePushButton = new QPushButton;
	scalePushButton->setText("OK");

	//vytvorim layout a pridam do neho spin boxy
	QHBoxLayout *scaleLayout = new QHBoxLayout;
	scaleLayout->addWidget(Label_x);
	scaleLayout->addWidget(scaleSpinBox_x);
	scaleLayout->addWidget(Label_y);
	scaleLayout->addWidget(scaleSpinBox_y);
	scaleLayout->addWidget(Label_z);
	scaleLayout->addWidget(scaleSpinBox_z);
	scaleLayout->addWidget(scalePushButton);

	//pridam layout do group boxu
	scaleGroupBox->setLayout(scaleLayout);

}*/

/*void bioData::createColorGroupBox()
{
	colorGroupBox = new QGroupBox(tr("Color"));

	QLabel *Min = new QLabel(tr("Min"));
	Min->setAlignment(Qt::AlignHCenter);
	colorSpinBox_min = new QDoubleSpinBox;
	colorSpinBox_min->setRange(-100.0, 100.0);
	colorSpinBox_min->setSingleStep(1.0);
	colorSpinBox_min->setValue(1.0);

	QLabel *Max = new QLabel(tr("Max"));
	Max->setAlignment(Qt::AlignHCenter);
	colorSpinBox_max = new QDoubleSpinBox;
	colorSpinBox_max->setRange(-100.0, 100.0);
	colorSpinBox_max->setSingleStep(1.0);
	colorSpinBox_max->setValue(1.0);

	QLabel *Palette = new QLabel(tr("Color palette"));
	Palette->setAlignment(Qt::AlignHCenter);
	colorComboBox = new QComboBox;
	colorComboBox->addItem("default");
	colorComboBox->addItem("1");
	colorComboBox->addItem("2");
	colorComboBox->addItem("3");
	colorComboBox->addItem("4");
	colorComboBox->setCurrentIndex(0);

	colorPushButton = new QPushButton;
	colorPushButton->setText("OK");

	QGridLayout *colorLayout = new QGridLayout;
	colorLayout->addWidget(Palette);
	colorLayout->addWidget(colorComboBox);
	colorLayout->addWidget(Min);
	colorLayout->addWidget(colorSpinBox_min);
	colorLayout->addWidget(Max);
	colorLayout->addWidget(colorSpinBox_max);
	colorLayout->addWidget(colorPushButton);

	colorGroupBox->setLayout(colorLayout);
}*/
