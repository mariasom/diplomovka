#include <QtWidgets/QMainWindow>
#include <QMetaObject>
#include <QSettings>
#include <QPixmap>
#include <QFileDialog>
#include <iostream>

#include "viewerWidget.h"
#include "source.h"

using namespace std;

#include <QFile>

#include "ui_bioData.h"
 
class bioData : public QMainWindow
{
  Q_OBJECT
public:
 
  bioData(); 
  ~bioData() {};

public slots:
	void actionOpenFile();

private:

  Ui::bioData *ui;
  viewerWidget* _vViewerWidget;
  source* _vData = new source;

};
