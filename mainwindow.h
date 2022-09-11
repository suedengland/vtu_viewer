#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include <QVTKOpenGLNativeWidget.h>

#include <vtkActor.h>
#include <vtkAxesActor.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkXMLUnstructuredGridReader.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slot_open_vtu();
    void slot_set_representation(QString);

private:
    Ui::MainWindow *ui;

    QString current_vtu_file = "";

    // vtk variables
    vtkSmartPointer<vtkXMLUnstructuredGridReader> reader;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkNamedColors> colors;
    vtkSmartPointer<vtkOrientationMarkerWidget> csys;
    vtkSmartPointer<vtkAxesActor> axes;
};

#endif // MAINWINDOW_H
