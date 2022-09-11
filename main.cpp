#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat()); // proposed in https://vtk.org/doc/nightly/html/classQVTKOpenGLNativeWidget.html
    QApplication a(argc, argv);
    a.setStyle(QString("windows")); // overrides the system's window style

    MainWindow w;
    w.show();

    return a.exec();
}
