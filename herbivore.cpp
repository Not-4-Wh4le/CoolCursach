#include "herbivore.h"

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}


Herbivore::Herbivore(QObject *parent):
    QObject(parent), QGraphicsItem(){
    setRotation(0);
}

Herbivore::~Herbivore(){};

QRectF Herbivore:: boundingRect() const {
    return QRectF(-50, -50, 100, 100);
}

void Herbivore::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawEllipse(-5, -5, 10, 10);
    painter->setBrush(QColor(231,204,138));
    painter->drawEllipse(-10,-22, 20, 44);

    painter->setBrush(Qt::white);
    painter->drawEllipse(-10, -17, 8, 8);
    painter->drawEllipse(2, -17, 8, 8);

    painter->setBrush(Qt::black);
    painter->drawEllipse(-8, -17, 4, 4);
    painter->drawEllipse(4, -17, 4, 4);

    painter->drawEllipse(QRectF(-2, -22, 4, 4));

    // painter->setBrush(Qt::darkYellow);
    // painter->drawEllipse(-17, -12, 16, 16);
    // painter->drawEllipse(1, -12, 16, 16);

    // QPainterPath path(QPointF(0, 22));
    // path.cubicTo(-5, 24, -5, 24, 0, 27);
    // path.cubicTo(5, 29, 5, 34, 0, 30);
    // path.cubicTo(-5, 34, -5, 44, 0, 37);
    // painter->setBrush(Qt::NoBrush);
    // painter->drawPath(path);

    Q_UNUSED(option);
    Q_UNUSED(widget);
};


qreal Herbivore:: getVision(){
    return vision;
}

qreal Herbivore:: getEnergy(){
    return energy;
}

qreal Herbivore:: getEnergyForFission(){
    return energyForFission;
}

void Herbivore:: increaseEnergy(){
    ++energy;
}


void Herbivore:: dicreaseEnergy(){
    energy /= 2;
}



void Herbivore::rotate() {
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
    qDebug() << closestFood;
}

void Herbivore:: move(){
    QLineF lineToTarget(QPoint(0,0), mapFromScene(closestFood));

    if(lineToTarget.length() > 5){
        setPos(mapToParent(0, -2));
    }
}
