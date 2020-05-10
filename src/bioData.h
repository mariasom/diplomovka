#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_bioData.h"

#include "viewerWidget.h"
#include "source.h"
#include "subWin.h"
#include "filters.h"
#include <filesystem>
#include <QKeyEvent>
#include <QDockWidget>

class bioData : public QMainWindow
{
	Q_OBJECT
public:

	bioData(QWidget *parent = 0);
	~bioData() {};
	bool eventFilter(QObject *obj, QEvent *event);
	bool QScrollAreaEventFilter(QObject *obj, QEvent *event);
	void setRangeValLab();
	void set3DWidget();
	void update3DWidget();
	void update2DWidget();
	void keyUpEvent(QKeyEvent *event);
	void keyDownEvent(QKeyEvent *event);
	void addSubItem(QTreeWidgetItem *parent, QString name);
	void initWin(QString path);
	void hideAllDocks();
	void showAllDocks();
	void disableMenuOpt();
	void enableMenuOpt();

	// groupboxes
	void createSubsurfGB();
	void createtestGB();
	void createGlobThrshldGB();
	void createLocThrshldGB();
	void initialConditionsGB();
	void createcontour3DGB();
	void createcontour2DGB();
	void createHeatEqGB();
	void createrManOptContourGB();
	void createCutDataAtGB();

	// docks
	void createFileDock(QString name, QString path, int width, int height);
	void createListDock();
	void createFilter2DDock();
	void createFilter3DDock();
	void createOptions2DDock();
	void createOptions3DDock();
	void createHistoryLogDock();

public slots:
	virtual void slotExit();

	void listIndexChanged(int i);
	void treeIndexChanged(QTreeWidgetItem *itm, int i);
	void colorIndexChanged(int i);
	// void actionFilters();

	// upper menu actions
	void actionHistLog();
	void actionAll();
	void actionFileInfo();
	void actionData();
	void actionOpenFile();
	void actionClose();
	void actionpgm();
	void action3Dvtkbinary();
	void action3Dvtkascii();
	void action2Dvtkbinary();
	void action2Dvtkascii();
	void action2DFilters();
	void action3DFilters();
	void actionAdvanced();
	void actionCloseFiles();

	// buttons actions
	void otsuClicked();
	void kapuraClicked();
	void niblackClicked();
	//void boundaryClicked();
	void bernsenClicked();
	void subsurfClicked();
	void actionSignDistFunc();
	void actionDistFunc();
	void twoDClicked();
	void threeDClicked();
	void deleteClicked();
	void resetViewClicked();
	void setDefaultValues();
	void saveScreenShot();
	void thresholdInitConClicked();
	void contour3DClicked();
	void contour2DClicked();
	void contour2DwIDClicked();
	void contour3DwDClicked();
	void differenceClicked();
	void heatEquationClicked();
	void contour3DPClicked();
	void contour3DPwDClicked();
	void manOptContClicked();
	void optContDispClicked();
	void histSavedClicked();
	void cutDataAtClicked();

	// others
	void AxesChange(bool checked);
	
	// testing
	void testClicked();

	//void createDockWindows();
	//void keyDown();
	//void keyUp();

private:
	Ui::bioData *ui;
	QMdiArea *mdiArea; 
	QWidget *widget = nullptr;
	QGridLayout *gridLayout;

	// docks
	QDockWidget *fileDock;
	QDockWidget *filter2DDock;
	QDockWidget *filter3DDock;
	QDockWidget *options2DDock;
	QDockWidget *options3DDock;
	QDockWidget *listDock;
	QDockWidget *subsurfDock;
	QDockWidget *historyDock;

	// groupboxes
	QGroupBox *subsurfGroupBox;
	QGroupBox *distanceGroupBox;
	QGroupBox *globThreshGroupBox;
	QGroupBox *locThreshGroupBox;
	QGroupBox *testGroupBox;
	QGroupBox *filterGB;
	QGroupBox *colorsGB;
	QGroupBox *scaleGroupBox;
	QGroupBox *colorGroupBox;
	QGroupBox *listGroupBox;
	QGroupBox *fileGroupBox;
	QGroupBox *initConGroupBox;
	QGroupBox *contour3DGroupBox;
	QGroupBox *contour2DGroupBox;
	QGroupBox *HeatEqGroupBox;
	QGroupBox *manOptContourGB;
	QGroupBox *cutDataAtGB;

	// treewidget + its items
	QTreeWidget *dataTree;
	QTreeWidgetItem *parent2D = nullptr;
	QTreeWidgetItem *parent3D = nullptr;

	// buttons
	QPushButton *otsuButton;
	QPushButton *kapuraButton;
	QPushButton *niblackButton;
	QPushButton *distanceButton;
	QPushButton *sDistanceButton;
	QPushButton *testingButton;
	QPushButton *subsurfButton;
	QPushButton *twoDButton;
	QPushButton *threeDButton;
	QPushButton *resetViewButton;
	QPushButton *delSelButton;
	QPushButton *openWinButton;
	QPushButton *bernsenButton;
	QPushButton *scalePushButton;
	QPushButton *colorPushButton;
	QPushButton *dataUp;
	QPushButton *dataDown;
	QPushButton *defaultValuesButton;
	QPushButton *screenshotButton;
	QPushButton *thresholdInitConButton;
	QPushButton *contour3DButton;
	QPushButton *contour2DButton;
	QPushButton *contour2DwIDButton;
	QPushButton *contour3DwDButton;
	QPushButton *differenceButton;
	QPushButton *heatEquationButton;
	QPushButton *contour3DPButton;
	QPushButton *contour3DPwDButton;
	QPushButton *manOptContourButton;
	QPushButton *contourOnOGButton;
	QPushButton *optContDispButton;
	QPushButton *histSaveButton;
	QPushButton *cutDataAtButton;

	// comboboxes
	QComboBox *dataCBox;
	QComboBox *initialCBox;
	QComboBox *colorCBox;

	// spinboxes
	QDoubleSpinBox *sigmaSubsurf;
	QDoubleSpinBox *tauSubsurf;
	QDoubleSpinBox *kSubsurf;
	QDoubleSpinBox *niblackTimeStepSB;
	QDoubleSpinBox *heatEqSB;
	QDoubleSpinBox *contourZConSB;
	QSpinBox *niblackMaskSB;
	QSpinBox *bernsenMaskSB;
	QSpinBox *numCont3DSB;
	QDoubleSpinBox *cutDataAtSB;

	//checkboxes
	QCheckBox *useOData;
	QCheckBox *axesCB;
	
	// other
	QLabel *rangeLab;
	QPlainTextEdit *historyText;
	QProgressBar *progBar;
	// garbage
	QTabWidget *innerTabs;
	QSpinBox *backgroundSB;
	QSpinBox *foregroundSB;;
	QListWidget *dataListView;
	int _index = 0;
	QVector<source*> _file;
	source *fTmp;
	QVector<viewerWidget*> _vWidget;
	QVector<subWin*> _winParam;
	viewerWidget* w;
	QString fName;
	QString filePath;
	bool advanced = false;
	filters filt;
};