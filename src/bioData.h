#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_bioData.h"

#include "viewerWidget.h"
#include "source.h"
#include "subWin.h"
#include "filters.h"
#include "help.h"
#include <filesystem>
#include <QHelpEngine>
#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QHelpSearchQueryWidget>


class bioData : public QMainWindow
{
	Q_OBJECT
public:

	bioData(QWidget *parent = 0);
	~bioData() {};
	bool eventFilter(QObject *obj, QEvent *event);
	bool QScrollAreaEventFilter(QObject *obj, QEvent *event);
	void setRangeValLab();
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
	void errorMessages(int i);

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
	void createListDock();
	void createFilter2DDock();
	void createFilter3DDock();
	void createOptions2DDock();
	void createOptions3DDock();
	void createHistoryLogDock();
	void createWindowsDock();
	void createHelpDock();

public slots:
	virtual void slotExit();

	void listIndexChanged(int i);
	void treeIndexChanged(QTreeWidgetItem *itm, int i);
	void colorIndexChanged(int i);

	// upper menu actions
	void actionHistLog();
	void actionAll();
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
	void actionCloseFiles();
	void actionHelp();
	void actionAbout();

	// buttons actions
	void otsuClicked();
	void kapuraClicked();
	void niblackClicked();
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
	void hybNBABernClicked();
	void sauvolaClicked();
	void hybSaBernClicked();
	void deleteWinClicked();
	void zlepsiVectorFieldClicked();
	void openWinClicked();

	// others
	void AxesChange(bool checked);
	
	// testing
	void testClicked();

private:
	Ui::bioData *ui;
	QMdiArea *mdiArea; 
	QVector<QMdiSubWindow*> _subW;
	QVector<source*> _file;
	QVector<viewerWidget*> _vWidget;
	QVector<subWin*> _winParam;
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
	QDockWidget *windowsDock;
	QDockWidget *helpDock;

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

	// treewidget, listView + its items
	QListWidget *winListView;
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
	QPushButton *hybNBABernButton;
	QPushButton *sauvolaButton;
	QPushButton *hybSaBernButton;
	QPushButton *deleteWinButton;
	QPushButton *zlepsiVectorFieldButton;

	// comboboxes
	QComboBox *dataCBox;
	QComboBox *initialCBox;
	QComboBox *colorCBox;
	QComboBox *gradTypeCBox;

	// spinboxes
	QDoubleSpinBox *sigmaSubsurf;
	QDoubleSpinBox *tauSubsurf;
	QDoubleSpinBox *kSubsurf;
	QDoubleSpinBox *niblackTimeStepSB;
	QDoubleSpinBox *heatEqSB;
	QDoubleSpinBox *contourZConSB;
	QDoubleSpinBox *NBaBrenTimeStepSB;
	QSpinBox *niblackMaskSB;
	QSpinBox *bernsenMaskSB;
	QSpinBox *numCont3DSB;
	QSpinBox *NBaBrenMaskSB;
	QSpinBox *timeStepsSubsurf;
	QDoubleSpinBox *cutDataAtSB;
	QDoubleSpinBox *sauvolaTimeStepSB;
	QDoubleSpinBox *SaBrenTimeStepSB;
	QSpinBox *sauvolaMaskSB;
	QSpinBox *SaBrenMaskSB;

	//checkboxes
	QCheckBox *useOData;
	QCheckBox *axesCB;
	
	// other
	QLabel *rangeLab;
	QPlainTextEdit *historyText;
	QProgressBar *progBar;

	// garbage
	int currentWin = 0;
	int indexOfVect = -1;
	int winSize = 0;
	bool subWinAdded = false;

	QString fName;
	QString filePath;
	filters filt;
};