#include "animalBase.h"

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}


AnimalBase::AnimalBase(QObject *parent):
    QObject(parent), QGraphicsItem(){
    setRotation(QRandomGenerator::global()->bounded(360));
    mutation();
}

AnimalBase::AnimalBase(const AnimalBase *p, QObject *parent):
    QObject(parent), QGraphicsItem(){
    setRotation(QRandomGenerator::global()->bounded(360));
    energy = p->energy;
    energyForFission = p->energyForFission;
    age = 0;
    speed = p->speed;
    vision = p->vision;
    size = p->size;
    damage = p->damage;
    herbivore = p->herbivore;
    predator = p->predator;
    protection = p->protection;
    timeToLife = p->timeToLife;
    _color = p->_color;
    timeEnergyDicrease = p->timeEnergyDicrease;
    this->setScale(size);
    mutation();
}

AnimalBase::AnimalBase(qreal predaror, qreal protection, qreal herbivore, QColor color, QObject *parent):
    QObject(parent), QGraphicsItem(){
    setRotation(QRandomGenerator::global()->bounded(360));
    this->predator = predaror;
    this->herbivore = herbivore;
    this->protection = protection;
    _color = color;
}



AnimalBase::~AnimalBase(){};

QRectF AnimalBase:: boundingRect() const {
    return QRectF(-50, -50, 100, 100);
}

void AnimalBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    qreal radius1 = 16;
    qreal radius2 = 26;
    int num = 16;
    qreal angleDelta = 2 * M_PI / num;
    painter->setPen(QPen(Qt::black, 1));
    for (int i = 0; i < num; ++i) {
        double angle = i * angleDelta;
        double x1 = radius1 * cos(angle);
        double y1 = radius2 * sin(angle);
        double x2 = radius1 * cos(angle + M_PI);
        double y2 = radius2 * sin(angle + M_PI);
        painter->drawLine(QLineF(x1, y1, x2, y2));
    }



    painter->drawEllipse(-5, -5, 10, 10);
    painter->setBrush(_color);
    painter->drawEllipse(-10,-22, 20, 44);

    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    painter->setBrush(Qt::black);
    painter->drawEllipse(-8, -17, 4, 4);
    painter->drawEllipse(4, -17, 4, 4);

    //painter->drawEllipse(QRectF(-2, -22, 4, 4));

    Q_UNUSED(option);
    Q_UNUSED(widget);
};


qreal AnimalBase:: getVision(){
    return vision;
}

qreal AnimalBase:: getAge(){
    return age;
}

qreal AnimalBase:: getDamage(){
    return damage;
}

qreal AnimalBase::getSize()
{
    return size;
}

qreal AnimalBase::getEnergyCost()
{
    return energyCost;
}

qreal AnimalBase::getProtecteion()
{
    return protection;
}


qreal AnimalBase:: getPredarot(){
    return predator;
}

qreal AnimalBase:: getHerbivore(){
    return herbivore;
}

qreal AnimalBase:: getEnergy(){
    return energy;
}

bool AnimalBase:: isOld(){
    return age>=timeToLife;
}

qreal AnimalBase::getSpeed()
{
    return speed;
}

qreal AnimalBase:: getEnergyForFission(){
    return energyForFission;
}


void AnimalBase:: increaseEnergy(){
    ++energy;
}


void AnimalBase:: increaseEnergy(qreal a){
    energy+=a;
}


void AnimalBase:: dicreaseEnergy(){
    energy /= 2;
}


void AnimalBase:: dicreaseEnergyTime(){
    energy -= energyCost;
}


void AnimalBase:: increaseAge(){
    ++age;
}

void AnimalBase::rotate() {
    QLineF lineToTarget(QPointF(0,0), mapFromScene(closestFood));
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0) {
        angleToTarget = M_PI - angleToTarget;
    }
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);
    if (angleToTarget >= 0 && angleToTarget < M_PI) {
        setRotation(rotation() + 5);
    } else if (angleToTarget >= 2*M_PI && angleToTarget < M_PI) {
        setRotation(rotation() - 5);
    }
}


void AnimalBase:: move(){
    // if (age>=timeToLife){
    //     die();
    //     return;
    // }
    //qDebug() << closestFood.x();
    QLineF lineToTarget(QPoint(0,0), closestFood);
    if(lineToTarget.length() > 5){
        setPos(mapToParent(0, -4 * speed / size));
    }
}

void AnimalBase:: die(){
    isAlive = false;
}


void AnimalBase:: mutation(){
    int chance = QRandomGenerator::global()->bounded(100);
    if (chance < mutationChange) {
        double mutationAmount = (QRandomGenerator::global()->bounded(20) - 10) / 100.0;
        int mutationType = QRandomGenerator::global()->bounded(7);
        int color;
        if (mutationType == 0) {
            speed += mutationAmount;
            size -= mutationAmount;
            energyCost += mutationAmount * 2;
            energyForFission -= mutationAmount * 10;
            vision -= mutationAmount * 20;
            color = _color.green() - mutationType * 10;
            color = qBound(0, color, 255);
            _color.setGreen(color);
        } else if (mutationType == 1) {
            size += mutationAmount;
            speed -= mutationAmount;
            energyForFission += mutationAmount * 10;
            energyCost += mutationAmount * 2;
            vision += mutationAmount * 50;
            color = _color.blue() - mutationType * 10;
            color = qBound(0, color, 255);
            _color.setGreen(color);
        } else if( mutationType == 2){
            damage += mutationAmount * 10;
            herbivore -= mutationAmount;
            predator +=mutationAmount;
            color = _color.red() + mutationType * 30;
            int color2 = _color.blue() - mutationType * 30;
            int color3 = _color.green() - mutationType * 30;
            color = qBound(0, color, 255);
            color2 = qBound(0, color2, 255);
            color3 = qBound(0, color3, 255);
            _color.setRed(color);
            _color.setBlue(color2);
            _color.setGreen(color3);
        } else if( mutationType == 3){
            protection += mutationAmount;
            damage -= mutationAmount;
            color = _color.red() + mutationType * 10;
            int color2 = _color.blue() + mutationType * 10;
            color = qBound(0, color, 255);
            color2 = qBound(0, color2, 255);
            _color.setRed(color);
            _color.setBlue(color2);
        } else if( mutationType == 4){
            speed += mutationAmount;
            energyCost += mutationAmount * 1.2;
        } else if( mutationType == 5){
            size += mutationAmount;
            energyCost += mutationAmount * 1.2;
        } else if( mutationType == 6){
            herbivore = 0.4;

            predator = 0.6;
            // vision += mutationAmount * 50;
            // energyCost += mutationAmount * 1.2;
        }

        speed = qBound(0.1, speed, 2.0);
        protection = qBound(0.0, protection, 2.0);
        herbivore = qBound(0.0, herbivore, 1.0);
        predator = qBound(0.0, predator, 1.0);
        damage = qBound(0.0, damage, 100.0);
        size = qBound(0.1, size, 2.0);
        vision = qBound(50.0, vision, 1000.0);
        energyForFission = qBound(3.0, energyForFission, 100.0);
        this->setScale(size);
        qDebug()<< speed << size << energyCost;
        //qDebug() << herbivore << predator << damage;
    }
}
