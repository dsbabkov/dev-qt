#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyScene.h"
#include <QActionGroup>
#include <QColorDialog>
#include "LineDialog.h"
#include "MyModel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyScene *scene = new MyScene(this);
    ui->graphicsView->setScene(scene);

    MyModel *model = new MyModel(this);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(scene, &MyScene::shapeAdded, model, &MyModel::addShape);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, [scene, model](const QModelIndex &index){
        scene->selectShape(model->rectAt(index.row()));
    });

    connect(ui->setColorAct, &QAction::triggered, this, &MainWindow::setColor);

    createLineEditDialog();

    connect(ui->rotateBtn, &QPushButton::clicked, [this]{ui->graphicsView->rotate(ui->angleSpn->value());});
    connect(ui->scaleBtn, &QPushButton::clicked, [this]{ui->graphicsView->scale(ui->scaleFactorSpn->value(), ui->scaleFactorSpn->value());});
    connect(ui->shearBtn, &QPushButton::clicked, [this]{ui->graphicsView->shear(ui->shearXSpn->value(), ui->shearYSpn->value());});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setColor()
{
    MyScene *scene = static_cast<MyScene *>(ui->graphicsView->scene());
    const QColor &color = QColorDialog::getColor(scene->color(), this,
                           tr("Color for scene pen"));

    if (color.isValid()){
        scene->setColor(color);
    }
}

void MainWindow::createLineEditDialog()
{
    LineDialog *lineDialog = new LineDialog(this);
    connect(ui->lineEditAct, &QAction::triggered, lineDialog, &LineDialog::exec);

    MyScene *scene = static_cast<MyScene *>(ui->graphicsView->scene());
    connect(lineDialog, &LineDialog::penAccepted, scene, &MyScene::setPen);
    connect(scene, &MyScene::penChanged, lineDialog, &LineDialog::setPen);
}
