#pragma once
#include <QtWidgets/QMainWindow>

#include "ui_bioData.h"

#include "viewerWidget.h"
#include "source.h"

class bioData : public QMainWindow
{
	Q_OBJECT
public:

	// Constructor/Destructor
	bioData();
	~bioData() {};
	bool eventFilter(QObject *obj, QEvent *event);
	bool QScrollAreaEventFilter(QObject *obj, QEvent *event);
	void visualize();

public slots:
	virtual void slotExit();
	void actionOpenFile();
	void actionClose();
	//void scaleClicked();
	//void colorClicked();

private:
	//void createScaleGroupBox();
	//void createColorGroupBox();

	Ui::bioData *ui;
	QTabWidget *_tabs = new QTabWidget();
	QDoubleSpinBox *scaleSpinBox_x;
	QDoubleSpinBox *scaleSpinBox_y;
	QDoubleSpinBox *scaleSpinBox_z;
	QDoubleSpinBox *colorSpinBox_min;
	QDoubleSpinBox *colorSpinBox_max;
	QComboBox *colorComboBox;
	QGroupBox *scaleGroupBox;
	QGroupBox *colorGroupBox;
	QPushButton *scalePushButton;
	QPushButton *colorPushButton;
	int _index = 0;
	source *_file;
	source *fTmp;
	viewerWidget *w;
	QString fName;
};