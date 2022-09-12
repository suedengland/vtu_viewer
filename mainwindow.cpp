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

    // initialize vtk
    renderer->SetBackground(colors->GetColor3d("Wheat").GetData());

    renderWindow = ui->qvtkwidget->QVTKOpenGLNativeWidget::renderWindow();
    renderWindow->AddRenderer(renderer);
    ui->qvtkwidget->update();

    // define connections between slots and signals
    QObject::connect(ui->actionOpenVTU, SIGNAL(triggered()), this, SLOT(slot_open_vtu()));
    QObject::connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(slot_set_representation(QString)));
    QObject::connect(ui->actionInformation, SIGNAL(triggered()), this, SLOT(slot_print_information()));
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

    // show file name in plainTextEdit
    ui->plainTextEdit->appendPlainText("New File opened:\n" + current_vtu_file + "\n");

    // remove existing mapper and actor
    mapper->RemoveAllObservers();
    renderer->RemoveActor(actor);

    // read vtu file
    reader->SetFileName(current_vtu_file.toStdString().c_str());
    reader->Update();
    number_of_points = reader->GetNumberOfPoints();
    number_of_cells = reader->GetNumberOfCells();
    number_of_pointArrays = reader->GetNumberOfPointArrays();
    number_of_cellArrays = reader->GetNumberOfCellArrays();

    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->ScalarVisibilityOff();

    actor->SetMapper(mapper);
    actor->SetOrigin(0.0, 0.0, 0.0);
    actor->GetProperty()->SetLineWidth(2.0);
    actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());

    actor->GetBounds(bounds);
    bounding_box[0] = bounds[1] - bounds[0]; // lx
    bounding_box[1] = bounds[3] - bounds[2]; // ly
    bounding_box[2] = bounds[5] - bounds[4]; // lz

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

void MainWindow::slot_print_information()
{
    // Number of Points, Cells, PointArrays, CellArrays
    // TODO: Number of cells by vtkCellTypes
    ui->plainTextEdit->appendPlainText("Number of points: " + QString::number(number_of_points));
    ui->plainTextEdit->appendPlainText("Number of cells: " + QString::number(number_of_cells)+ "\n");
    ui->plainTextEdit->appendPlainText("Number of point arrays: " + QString::number(number_of_pointArrays));
    if (number_of_pointArrays > 0) {
        ui->plainTextEdit->appendPlainText("{");
        for (int i=0; i<number_of_pointArrays; i++) {
            ui->plainTextEdit->appendPlainText("\t" + QString(reader->GetPointArrayName(i)));
        }
        ui->plainTextEdit->appendPlainText("}");
    }
    ui->plainTextEdit->appendPlainText("Number of cell arrays: " + QString::number(number_of_cellArrays) + "\n");

    // Bounding Box
    ui->plainTextEdit->appendPlainText("Bounding Box:");
    ui->plainTextEdit->appendPlainText("Limits:");
    ui->plainTextEdit->appendPlainText("\tx-, x+: " + QString::number(bounds[0]) + ", " + QString::number(bounds[1]));
    ui->plainTextEdit->appendPlainText("\ty-, y+: " + QString::number(bounds[2]) + ", " + QString::number(bounds[3]));
    ui->plainTextEdit->appendPlainText("\tz-, z+: " + QString::number(bounds[4]) + ", " + QString::number(bounds[5]) + "\n");
    ui->plainTextEdit->appendPlainText("Size:");
    ui->plainTextEdit->appendPlainText("\tlx = " + QString::number(bounding_box[0]));
    ui->plainTextEdit->appendPlainText("\tly = " + QString::number(bounding_box[1]));
    ui->plainTextEdit->appendPlainText("\tlz = " + QString::number(bounding_box[2]) + "\n");
}
