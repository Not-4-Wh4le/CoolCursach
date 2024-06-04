#include "food.h"



Food::Food(QObject *parent):
    QObject(parent), QGraphicsItem(){

}

Food::~Food(){};

QRectF Food:: boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(Qt::green);
    painter->setBrush(Qt::green);
        painter->drawEllipse(-5, -5, 10, 10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
};

void Food:: eatFood(){
    isEaten = true;
}
