#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_bioData.h"

#include "viewerWidget.h"
#include "source.h"
#include "filters.h"
#include <filesystem>
#include <QKeyEvent>
#include <QDockWidget>

class bioData : public QMainWindow
{
	Q_OBJECT
public:

	// Constructor/Destructor
	bioData(QWidget *parent = 0);
	~bioData() {};
	bool eventFilter(QObject *obj, QEvent *event);
	bool QScrollAreaEventFilter(QObject *obj, QEvent *event);
	//void visualize();
	void setTabWidget();
	//void createInfoGroupBox();
	void createFileDock(QString name, QString path, int width, int height);
	void createListDock();
	void createFilterDock();
	void createSubsurfDock();
	void createSubsurfGB();
	void createDistanceGB();
	void createColorsGB();
	void createtestGB();
	void set3DWidget();
	void update3DWidget();
	void set2DWidget();
	void update2DWidget();
	void createDockWidgets();
	void keyUpEvent(QKeyEvent *event);
	void keyDownEvent(QKeyEvent *event);
	void addSubItem(QTreeWidgetItem *parent, QString name);

public slots:
	virtual void slotExit();
	void actionOpenFile();
	void actionClose();
	void actionpgm();
	void actionvtkbinary();
	void actionvtkascii();
	void actionAdvanced();
	void otsuClicked();
	void kapuraClicked();
	void niblackClicked();
	void boundaryClicked();
	void subsurfClicked();
	void listIndexChanged(int i);
	void treeIndexChanged(QTreeWidgetItem *itm, int i);
	void actionSignDistFunc();
	void actionDistFunc();
	void actionAll();
	void actionFileInfo();
	void actionData();
	void actionFilters();
	void deleteClicked();
	void resetViewClicked();
	void actionCloseFiles();
	void twoDClicked();
	void threeDClicked();

	void testClicked();

	//void createDockWindows();
	//void keyDown();
	//void keyUp();

private:
	Ui::bioData *ui;
	QMdiArea *mdiArea;
	QWidget *widget2D = nullptr;
	QWidget *widget3D = nullptr;
	QGridLayout *gridLayout2D;
	QGridLayout *gridLayout3D;
	QDockWidget *fileDock;
	QDockWidget *filterDock;
	QDockWidget *listDock;
	QDockWidget *subsurfDock;
	QTreeWidget *dataTree;
	QTreeWidgetItem *parent2D;
	QTreeWidgetItem *parent3D;
	QComboBox *dataCBox;
	QPushButton *subsurfButton;
	QDoubleSpinBox *sigmaSubsurf;
	QDoubleSpinBox *tauSubsurf;
	QDoubleSpinBox *kSubsurf;
	QGroupBox *subsurfGroupBox;
	QGroupBox *distanceGroupBox;
	QPushButton *distanceButton;
	QPushButton *sDistanceButton;
	QPushButton *testingButton;
	QGroupBox *testGroupBox;
	QPushButton *twoDButton;
	QPushButton *threeDButton;
	QPushButton *resetViewButton; 
	QPushButton *delSelButton;
	QPushButton *openWinButton;
	
	QTabWidget *innerTabs;
	QDoubleSpinBox *scaleSpinBox_x;
	QDoubleSpinBox *scaleSpinBox_y;
	QDoubleSpinBox *scaleSpinBox_z;
	QSpinBox *backgroundSB;
	QSpinBox *foregroundSB;;
	QComboBox *colorComboBox;
	QGroupBox *scaleGroupBox;
	QGroupBox *colorGroupBox;
	QGroupBox *listGroupBox;
	QGroupBox *filterGB;
	QGroupBox *colorsGB;
	QPushButton *scalePushButton;
	QPushButton *colorPushButton;
	QPushButton *dataUp;
	QPushButton *dataDown;
	QPushButton *otsuButton;
	QPushButton *kapuraButton;
	QPushButton *niblackButton;
	QPushButton *boundaryButton;
	QGroupBox *fileGroupBox;
	QListWidget *dataListView;
	QCheckBox *useOData;
	QCheckBox *originalCol;
	int _index = 0;
	source *_file;
	source *fTmp;
	viewerWidget *w;
	QString fName;
	QString filePath;
	bool advanced = false;
	filters filt;
};