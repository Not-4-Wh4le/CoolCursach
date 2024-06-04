#include "animalscene.h"
#include "ui_animalscene.h"
#include <QRandomGenerator>
#include <QGraphicsRectItem>


AnimalScene::AnimalScene(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnimalScene)
{
    scene = new QGraphicsScene();

    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &AnimalScene::changeSpeed);

    timer = new QTimer(this);
    lifeTimer = new QTimer(this);
    foodTimer = new QTimer(this);

}

AnimalScene::~AnimalScene()
{
    delete ui;
}

void AnimalScene:: start(int fieldSize, int bacteriaCount, int foodCount, int mutationChance){
    charts = new PopulationCharts();
    custom = new CustomAnimal();
    connect(this, &AnimalScene:: updateChartsSignal, charts, &PopulationCharts:: updateCharts);
    for (int i = 1; i <= 20; ++i){
        speed[i] = 0;
        protection[i] = 0;
        size[i] = 0;
    }

    ui->inf->addWidget(charts);
    charts->hide();
    connect(timer, &QTimer::timeout, this, &AnimalScene::behavior);
    connect(foodTimer, &QTimer::timeout, this, &AnimalScene::createNewFood);
    connect(lifeTimer, &QTimer:: timeout, this, &AnimalScene::updateCharts);
    lastFood = QTime::currentTime();
    programSpeed = 60 - ui->speedSlider->value();
    scene->setSceneRect(0,0, fieldSize, fieldSize);
    scene->addRect(QRectF(0, 0, scene->width(),scene->height()));
    AnimalBase:: mutationChange = mutationChance;
    for (int i = 0; i < bacteriaCount; ++i){
        AnimalBase *animal = new AnimalBase();
        scene->addItem(animal);
        int x = rand() % static_cast<int>(scene->width());
        int y = rand() % static_cast<int>(scene->height());
        animal->setPos(x, y);
        animalList.append(animal);
        ++speed[(qCeil(animal->getSpeed() * 10))];
        ++size[(qCeil(animal->getSize() * 10))];
        ++protection[(qCeil(animal->getEnergyCost() * 10))];
        connect(lifeTimer, &QTimer::timeout, animal, &AnimalBase::increaseAge);
        connect(lifeTimer, &QTimer::timeout, animal, &AnimalBase::dicreaseEnergyTime);
    }
    for (int i = 0; i < foodCount; ++i){
        Food *food = new Food();
        int x = rand() % static_cast<int>(scene->width());
        int y = rand() % static_cast<int>(scene->height());
        food->setPos(x, y);
        scene->addItem(food);
        foodList.append(food);
    }
    timer->start(programSpeed);
    lifeSpeed = qRound(programSpeed*1000/30.0);
    lifeTimer->start(lifeSpeed);
    lifeSpeed = qRound(programSpeed*50/30.0);
    foodTimer->start(lifeSpeed);
}


// void AnimalScene:: on_stopBtn_clicked(){
//     this->close();
//     // AnimalBase *animal = new AnimalBase(0.5, 0.5, 0, QColor(255,10,20));
//     // scene->addItem(animal);
//     // int x = rand() % static_cast<int>(scene->width());
//     // int y = rand() % static_cast<int>(scene->height());
//     // animal->setPos(x, y);
//     // qDebug() << animal->getPredarot() << animal->getHerbivore();
//     // animalList.append(animal);
// }



// void AnimalScene:: slotTimer(){
//     if(lastFood.msecsTo(QTime::currentTime()) >= programSpeed * 50 / 30){
//         createNewFood();
//         lastFood = QTime::currentTime();
//     }
//     behavior();
// }

void AnimalScene::changeSpeed()
{
    programSpeed = 60 - ui->speedSlider->value();
    timer->setInterval(programSpeed);
    lifeSpeed = qRound(programSpeed*1000/30.0);
    lifeTimer->setInterval(lifeSpeed);
    lifeSpeed = qRound(programSpeed*50/30.0);
    foodTimer->setInterval(lifeSpeed);

}

void AnimalScene:: createNewFood(){
    Food *food = new Food();
    int x = rand() % static_cast<int>(scene->width());
    int y = rand() % static_cast<int>(scene->height());
    food->setPos(x, y);
    scene->addItem(food);
    foodList.append(food);
}

void AnimalScene::updateCharts()
{
    emit updateChartsSignal(animalList.size(), speed, protection, size);
}


void AnimalScene:: predatorBehavior(AnimalBase* animal){
    AnimalBase *closestFood = nullptr;
    qreal minDist = scene->height() * scene->height() + scene->width() * scene->width();
    for(auto food : animalList){
        if(!food->isAlive) continue;
        if(food == animal) continue;
        if (animal->getPredarot() <= food->getPredarot() + 0.2) continue;
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
        QPointF point(closestFood->x(), closestFood->y());
        animal->closestFood = point;
        if (minDist < 625 * animal->scale()){
            animal->increaseEnergy(closestFood->getEnergy() * 0.5);
            closestFood->die();
        }
    }
    else{
        qreal x = QRandomGenerator::global()->bounded(0, (int)scene->width());
        qreal y = QRandomGenerator::global()->bounded(0, (int)scene->height());
        animal->closestFood = QPointF(x, y);
    }
}

void AnimalScene:: herbivoreBehavior(AnimalBase* animal){
    Food *closestFood = nullptr;
    qreal minDist = scene->height() * scene->height() + scene->width() * scene->width();
    for(auto food : foodList){
        if(food->isEaten) continue;
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
        QPointF point(closestFood->x(), closestFood->y());
        animal->closestFood = point;
        if (minDist < 625 * animal->scale()){
            animal->increaseEnergy();
            closestFood->eatFood();
        }
    }
    else{
        if(animal->getPredarot()>=0.1){
            predatorBehavior(animal);
        }
        else{
            qreal x = QRandomGenerator::global()->bounded(0, (int)scene->width());
            qreal y = QRandomGenerator::global()->bounded(0, (int)scene->height());
            animal->closestFood = QPointF(x, y);
        }

    }
}




void AnimalScene:: behavior(){
    for(int i = 0; i < animalList.size(); ++i){
        AnimalBase* animal = animalList[i];
        animal->move();
        animal->rotate();
        if(animal->x() < 0){
            animal->setX(animal->x() + 5);
            qreal rotation = QRandomGenerator::global()->bounded(90, 270);
            animal->setRotation(animal->rotation() + rotation);
        }
        else if (animal->x() > scene->width()){
            animal->setX(animal->x() - 5);
            qreal rotation = QRandomGenerator::global()->bounded(90, 270);
            animal->setRotation(animal->rotation() + rotation);
        }
        if(animal->y() < 0){
            animal->setY(animal->y() + 5);
            qreal rotation = QRandomGenerator::global()->bounded(90, 270);
            animal->setRotation(animal->rotation() + rotation);
        }
        else if (animal->y() > scene->height()){
            animal->setY(animal->y() - 5);
            qreal rotation = QRandomGenerator::global()->bounded(90, 270);
            animal->setRotation(animal->rotation() + rotation);
        }
        if(animal->getAge() > 0.5){
            if(animal->getHerbivore() >= animal->getPredarot()){

                herbivoreBehavior(animal);
            }
            else{
                predatorBehavior(animal);
            }

            if(animal->getEnergyForFission() < animal->getEnergy()){
                animal->dicreaseEnergy();
                AnimalBase* child = new AnimalBase(animal);
                child->setPos(animal->x()-5, animal->y()-5);
                animalList.append(child);
                connect(lifeTimer, &QTimer::timeout, child, &AnimalBase::increaseAge);
                connect(lifeTimer, &QTimer::timeout, child, &AnimalBase::dicreaseEnergyTime);
                scene->addItem(child);
                ++speed[qCeil(child->getSpeed() * 10)];
                ++protection[(qCeil(child->getEnergyCost() * 10))];
                ++size[(qCeil(child->getSize() * 10))];

            }
        }

        if(animal->getEnergy() < 0 || animal->isOld()){
            animal->die();
        }

        if (!animal->isAlive){
            scene->removeItem(animal);
            animalList.removeAt(i);
            --speed[qCeil(animal->getSpeed() * 10)];
            --protection[(qCeil(animal->getEnergyCost() * 10))];
            --size[(qCeil(animal->getSize() * 10))];
            delete animal;
            animal= nullptr;
            --i;
           continue;
        }
    }
    for (int i = 0; i < foodList.size(); ++i) {
        if(foodList[i]->isEaten) {
            auto closestFood = foodList[i];
            foodList.removeAt(i);
            scene->removeItem(closestFood);
            delete closestFood;
            closestFood = nullptr;
            --i;
        }
    }
}

void AnimalScene::on_resumeButton_clicked()
{
    ui->pauseButton->setEnabled(1);
    ui->resumeButton->setEnabled(0);
    foodTimer->start();
    lifeTimer->start();
    timer->start();
}


void AnimalScene::on_pauseButton_clicked()
{
    ui->pauseButton->setEnabled(0);
    ui->resumeButton->setEnabled(1);
    foodTimer->stop();
    lifeTimer->stop();
    timer->stop();
}


void AnimalScene::on_completeButton_clicked()
{
    ui->pauseButton->setEnabled(1);
    ui->resumeButton->setEnabled(1);
    ui->speedSlider->setValue(29);
    foodTimer->stop();
    foodTimer->disconnect();
    lifeTimer->stop();
    lifeTimer->disconnect();
    timer->stop();
    timer->disconnect();
    for (auto food : foodList){
        delete food;
    }
    foodList.clear();

    for (auto animal : animalList){
        delete animal;
    }
    animalList.clear();
    ui->graphicsView->show();
    charts->hide();
    scene->clear();
    this->close();
    ui->inf->removeWidget(charts);
    delete charts;
    emit completeSignal();

}



void AnimalScene::on_switchButton_clicked()
{
    if(charts->isVisible()){
        charts->hide();
        ui->graphicsView->show();
        ui->switchButton->setText("Графики");

    }
    else{
        charts->show();
        ui->graphicsView->hide();

        ui->switchButton->setText("Сцена");
    }
}


void AnimalScene::on_customAnimalButton_clicked()
{

}


void AnimalScene::on_settingAnimalButton_clicked()
{
    custom->show();
}

