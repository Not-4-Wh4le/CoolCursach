#ifndef HERBIVORE_H
#define HERBIVORE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

class Herbivore : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Herbivore(QObject *parent = nullptr);
    ~Herbivore();
    void increaseEnergy();
    void dicreaseEnergy();
    qreal getEnergy();
    int getAge();
    qreal getSpeed();
    qreal getEnergyForFission();
    qreal getVision();
    QPointF closestFood;
    void rotate();
    void move();


signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal energy = 0;
    qreal energyForFission = 6;
    int age;
    qreal speed = 1;
    qreal vision = 100;

public slots:

};

#endif // HERBIVORE_H
