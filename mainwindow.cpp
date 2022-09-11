#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    reader(vtkSmartPointer<vtkXMLUnstructuredGridReader>::New()),
    mapper(vtkSmartPointer<vtkDataSetMapper>::New()),
    actor(vtkSmartPointer<vtkActor>::New()),
    renderer(vtkSmartPointer<vtkRenderer>::New()),
    renderWindow(vtkSmartPointer<vtkRenderWindow>::New()),
    colors(vtkSmartPointer<vtkNamedColors>::New()),
    csys(vtkSmartPointer<vtkOrientationMarkerWidget>::New()),
    axes(vtkSmartPointer<vtkAxesActor>::New())
{
    ui->setupUi(this);

    // window title
    setWindowTitle("VTU viewer");

    // initialize lineEdit containing the file name
    ui->lineEdit->setText(current_vtu_file);

    // initialize vtk
    renderer->SetBackground(colors->GetColor3d("Wheat").GetData());

    renderWindow = ui->qvtkwidget->QVTKOpenGLNativeWidget::renderWindow();
    renderWindow->AddRenderer(renderer);
    ui->qvtkwidget->update();

    // define connections between slots and signals
    QObject::connect(ui->actionOpenVTU, SIGNAL(triggered()), this, SLOT(slot_open_vtu()));
    QObject::connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_set_representation(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_open_vtu()
{
    // open file dialog
    QString vtu_filename = QFileDialog::getOpenFileName(this, "tr(Datei öffnen)", "", "vtu (*vtu *vtk)");
    current_vtu_file = vtu_filename;

    // show file name in lineEdit
    ui->lineEdit->setText(current_vtu_file);

    // remove existing mapper and actor
    mapper->RemoveAllObservers();
    renderer->RemoveActor(actor);

    // read vtu file
    reader->SetFileName(current_vtu_file.toStdString().c_str());
    reader->Update();

    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->ScalarVisibilityOff();

    actor->SetMapper(mapper);
    actor->SetOrigin(0.0, 0.0, 0.0);
    actor->GetProperty()->SetLineWidth(2.0);
    actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());

    renderer->AddActor(actor);
    renderer->ResetCamera();

    axes->SetShaftTypeToLine();
    axes->SetTotalLength(1.0, 1.0, 1.0);
    axes->SetXAxisLabelText("x");
    axes->SetYAxisLabelText("y");
    axes->SetZAxisLabelText("z");

    csys->SetOutlineColor(0.93, 0.57, 0.13);
    csys->SetOrientationMarker(axes);
    csys->SetInteractor(renderWindow->GetInteractor());
    csys->SetViewport(0.0, 0.0, 0.3, 0.3);
    csys->SetEnabled(1);
    csys->InteractiveOff();

    // apply current representation, render and update view
    slot_set_representation(ui->comboBox->currentText());
}

void MainWindow::slot_set_representation(QString representation)
{
    if (representation == "Points") {
        actor->GetProperty()->SetRepresentationToPoints();
        actor->GetProperty()->EdgeVisibilityOff();
    } else if (representation == "Surface") {
        actor->GetProperty()->SetRepresentationToSurface();
        actor->GetProperty()->EdgeVisibilityOff();
    } else if (representation == "Surface with Edges") {
        actor->GetProperty()->SetRepresentationToSurface();
        actor->GetProperty()->EdgeVisibilityOn();
    } else if (representation == "Wireframe") {
        actor->GetProperty()->SetRepresentationToWireframe();
        actor->GetProperty()->EdgeVisibilityOff();
    }

    renderWindow->Render();
    ui->qvtkwidget->update();
}
