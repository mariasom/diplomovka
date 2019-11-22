#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_bioData.h"

#include "viewerWidget.h"
#include "source.h"
#include "filters.h"
#include <filesystem>
#include <QKeyEvent>

class bioData : public QMainWindow
{
	Q_OBJECT
public:

	// Constructor/Destructor
	bioData(QWidget *parent = 0);
	~bioData() {};
	bool eventFilter(QObject *obj, QEvent *event);
	bool QScrollAreaEventFilter(QObject *obj, QEvent *event);
	void visualize();
	void setTabWidget();
	//void createInfoGroupBox();
	void createFileGroupBox(QString name, QString path, int width, int height);
	void createListGroupBox();
	void createFilterGB();
	void keyUpEvent(QKeyEvent *event);
	void keyDownEvent(QKeyEvent *event);

public slots:
	virtual void slotExit();
	void actionOpenFile();
	void actionClose();
	void actionpgm();
	void actionAdvanced();
	void otsuClicked();
	void kapuraClicked();
	void listIndexChanged(int i);
	//void keyDown();
	//void keyUp();

private:
	//void createScaleGroupBox();
	//void createColorGroupBox();

	Ui::bioData *ui;
	QTabWidget *_tabs = new QTabWidget();
	QTabWidget *innerTabs;
	QDoubleSpinBox *scaleSpinBox_x;
	QDoubleSpinBox *scaleSpinBox_y;
	QDoubleSpinBox *scaleSpinBox_z;
	QDoubleSpinBox *colorSpinBox_min;
	QDoubleSpinBox *colorSpinBox_max;
	QComboBox *colorComboBox;
	QGroupBox *scaleGroupBox;
	QGroupBox *colorGroupBox;
	QGroupBox *listGroupBox;
	QGroupBox *filterGB;
	QPushButton *scalePushButton;
	QPushButton *colorPushButton;
	QPushButton *dataUp;
	QPushButton *dataDown;
	QPushButton *otsuButton;
	QPushButton *kapuraButton;
	QGroupBox *fileGroupBox;
	QListWidget *dataListView;
	int _index = 0;
	source *_file;
	source *fTmp;
	viewerWidget *w;
	QString fName;
	QString filePath;
	bool advanced = false;
	filters filt;
};