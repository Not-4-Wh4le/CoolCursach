#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <QGraphicsRectItem>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mutationChanceSlider, &QSlider::valueChanged, this, &MainWindow::updateMutationChanceLabel);
    scene = new AnimalScene();
    connect(this, &MainWindow:: startSignal, scene, &AnimalScene::start);
    connect(scene, &AnimalScene:: completeSignal, this, &MainWindow::completeSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    emit startSignal(ui->fieldSizeBox->value(), ui->bacteriaCountBox->value(),
                     ui->foodCountBox->value(), ui->mutationChanceSlider->value());
    scene->show();
    this->hide();
}

void MainWindow::completeSlot()
{
    this->show();
}

void MainWindow:: updateMutationChanceLabel(int value){
    ui->labelChanceNum->setText(QString::number(value));

}



