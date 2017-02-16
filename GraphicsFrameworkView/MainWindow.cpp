#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyScene.h"
#include <QActionGroup>
#include <QColorDialog>
#include "LineDialog.h"
#include "MyModel.h"
#include "MyDelegate.h"
#include "DataBaseManager.h"
#include <QSqlTableModel>

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
    ui->tableView->setItemDelegate(new MyDelegate(this));
    connect(scene, &MyScene::shapeAdded, model, &MyModel::addShape);
    connect(model, &MyModel::shapeChanged, scene, &MyScene::changeShape);
    connect(model, &MyModel::cleared, scene, &MyScene::clear);
    connect(ui->clearAct, &QAction::triggered, model, &MyModel::clear);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentRowChanged, [scene, model](const QModelIndex &index){
        scene->selectShape(model->rectAt(index.row()));
    });

    connect(ui->setColorAct, &QAction::triggered, this, &MainWindow::setColor);

    createLineEditDialog();

    connect(ui->rotateBtn, &QPushButton::clicked, [this]{ui->graphicsView->rotate(ui->angleSpn->value());});
    connect(ui->scaleBtn, &QPushButton::clicked, [this]{ui->graphicsView->scale(ui->scaleFactorSpn->value(), ui->scaleFactorSpn->value());});
    connect(ui->shearBtn, &QPushButton::clicked, [this]{ui->graphicsView->shear(ui->shearXSpn->value(), ui->shearYSpn->value());});

    createDatabaseManager();
    connect(ui->tableModelAct, &QAction::triggered, this, &MainWindow::showSqlTableView);
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

void MainWindow::createDatabaseManager()
{
    DataBaseManager *dbMan = new DataBaseManager(this);

    connect(ui->createConnectionAct, &QAction::triggered, dbMan, &DataBaseManager::createConnection);
    connect(ui->createTableAct, &QAction::triggered, dbMan, &DataBaseManager::createTable);
    connect(ui->writeToBdAct, &QAction::triggered, [this, dbMan]{dbMan->writeTable(
                    static_cast<MyModel *>(ui->tableView->model())->rects());});
    connect(ui->readFromBdAct, &QAction::triggered, dbMan, &DataBaseManager::readTable);
    connect(dbMan, &DataBaseManager::shapeRead, static_cast<MyScene *>(ui->graphicsView->scene()), &MyScene::addShape);
}

void MainWindow::showSqlTableView()
{
    QDialog dialog;
    dialog.setLayout(new QVBoxLayout(&dialog));

    QSqlTableModel model;
    model.setTable("rectangle");
    model.select();

    QTableView view;
    view.setModel(&model);

    dialog.layout()->addWidget(&view);
    dialog.exec();
}
