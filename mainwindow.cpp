#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,600);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    lastFood = QTime::currentTime();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow:: on_startBtn_clicked(){
    Herbivore *animal = new Herbivore();
    scene->addItem(animal);
    int x = rand() % static_cast<int>(scene->width());
    int y = rand() % static_cast<int>(scene->height());
    animal->setPos(x, y);
    animalList.append(animal);
    timer->start(30);
}


void MainWindow:: slotTimer(){
    if(lastFood.msecsTo(QTime::currentTime()) >= 150){
        createNewFood();
        lastFood = QTime::currentTime();
    }
    behavior();
}


void MainWindow:: createNewFood(){
    Food *food = new Food();
    int x = rand() % static_cast<int>(scene->width());
    int y = rand() % static_cast<int>(scene->height());
    food->setPos(x, y);
    scene->addItem(food);
    foodList.append(food);
}

void MainWindow:: behavior(){
    for(auto animal : animalList){
        //QLineF lineToTarget(animal->mapToParent(QPoint(0,0)), animal->mapFromScene(animal->closestFood));
        animal->rotate();
        animal->move();
        if(animal->x() < 0){
            animal->setX(animal->x() + 5);
        }
        else if (animal->x() > scene->width()){
            animal->setX(animal->x() - 5);
        }
        if(animal->y() < 0){
            animal->setY(animal->y() + 5);
        }
        else if (animal->y() > scene->height()){
            animal->setY(animal->y() - 5);
        }
        //qDebug() << animal->closestFood;
        // qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
        // if (lineToTarget.dy() < 0)
        //     angleToTarget = 2* M_PI - angleToTarget;
        // angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);

        // // Поворачиваем героя к цели
        // if (angleToTarget >= 0 && angleToTarget < M_PI) {
        //     // Rotate left
        //     setRotation(rotation() - angleToTarget * 180 /M_PI);
        // } else if (angleToTarget <= 2*M_PI && angleToTarget > M_PI) {
        //     // Rotate right
        //     setRotation(rotation() + (angleToTarget - 2* M_PI )* (-180) /M_PI);
        // }
       // if(lineToTarget.length() > 5){
         //   animal->setPos(animal->mapToParent(0, -2));
            //->setPos(mapToParent(0, -2));
        //}ё

        Food *closestFood = nullptr;
        qreal minDist = scene->height() * scene->height() + scene->width() * scene->width();
        for(auto food : foodList){
            qreal x = animal->x() - food->x();
            qreal y = animal->y() - food->y();
            qreal distToFood = x * x + y * y;
            if(distToFood < animal->getVision() * animal->getVision()){
                if(distToFood < minDist){
                    minDist = distToFood;
                    closestFood = food;
                }
            }
        }
        if(closestFood!=nullptr){
            //QPointF point(closestFood->x() - animal->x(), closestFood->y() - animal->y());
            QPointF point(closestFood->x(), closestFood->y());
            animal->closestFood = point;
            if (minDist < 625){
                animal->increaseEnergy();
                foodList.removeOne(closestFood);
                scene->removeItem(closestFood);
                delete closestFood;
                closestFood = nullptr;
            }
        }
        else{
            qreal angle = QRandomGenerator::global()->bounded(0, 100) * M_PI * 2;
            animal->closestFood = QPointF(std::cos(angle) * 2, std::sin(angle) * 2);

        }
        if(animal->getEnergyForFission() < animal->getEnergy()){
            animal->dicreaseEnergy();
            Herbivore* child = new Herbivore();
            child->setPos(animal->x()-5, animal->y()-5);
            animalList.append(child);
            scene->addItem(child);
        }
    }
}
