#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

#include "bioData.h"
 
int main( int argc, char** argv )
{
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  // QT Stuff
  QApplication app( argc, argv );
 
  bioData bioData;
  bioData.show();
 
  return app.exec();
}
