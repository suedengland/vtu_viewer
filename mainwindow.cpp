#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    reader(vtkSmartPointer<vtkXMLUnstructuredGridReader>::New()),
    mapper(vtkSmartPointer<vtkDataSetMapper>::New()),
    actor(vtkSmartPointer<vtkActor>::New()),
    renderer(vtkSmartPointer<vtkRenderer>::New()),
    colors(vtkSmartPointer<vtkNamedColors>::New())
{
    ui->setupUi(this);

    // window title
    setWindowTitle("VTU viewer");

    // initialize vtk
    renderer->SetBackground(colors->GetColor3d("Wheat").GetData());
    ui->qvtkwidget->QVTKOpenGLNativeWidget::renderWindow()->AddRenderer(renderer);
    ui->qvtkwidget->update();

    // initialize lineEdit containing the file name
    ui->lineEdit->setText(current_vtu_file);

    // slots und signals
    QObject::connect(ui->actionOpenVTU, SIGNAL(triggered()), this, SLOT(slot_open_vtu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_open_vtu()
{
    QString vtu_filename = QFileDialog::getOpenFileName(this, "tr(Datei öffnen)", "", "vtu (*vtu *vtk)");
    current_vtu_file = vtu_filename;

    ui->lineEdit->setText(current_vtu_file);

    reader->SetFileName(current_vtu_file.toStdString().c_str());
    reader->Update();

    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->ScalarVisibilityOff();

    actor->SetMapper(mapper);
    actor->SetOrigin(0,0,0);
    actor->GetProperty()->EdgeVisibilityOn();
    actor->GetProperty()->SetLineWidth(2.0);
    actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());

    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("Wheat").GetData());

    ui->qvtkwidget->QVTKOpenGLNativeWidget::renderWindow()->AddRenderer(renderer);
    ui->qvtkwidget->update();
}
