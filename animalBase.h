#ifndef ANIMALBASE_H
#define ANIMALBASE_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>

class AnimalBase : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit AnimalBase(QObject *parent = nullptr);
    explicit AnimalBase(const AnimalBase* p, QObject *parent = nullptr);
    explicit AnimalBase(qreal, qreal, qreal, QColor, QObject *parent = nullptr);
    ~AnimalBase();
    void increaseEnergy();
    void increaseEnergy(qreal);
    void dicreaseEnergy();
    qreal getEnergy();
    bool isAlive = true;
    qreal getAge();
    bool isOld();
    qreal getSpeed();
    qreal getEnergyForFission();
    qreal getVision();
    qreal getPredarot();
    qreal getHerbivore();
    qreal getDamage();
    qreal getSize();
    qreal getEnergyCost();
    qreal getProtecteion();
    QPointF closestFood = QPointF(1, 1);
    // QTimer *lifeTimer;
    // QTimer *energyTimer;
    void rotate();
    void move();

    void die();
    static inline int mutationChange;


signals:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal energy = 5;
    qreal energyForFission = 10;
    qreal age = 0;
    qreal speed = 0.5;
    qreal vision = 200;
    qreal size = 1;
    qreal damage = 0;
    qreal herbivore = 1;
    qreal predator = 0;
    qreal protection = 0;
    qreal timeToLife = 32;
    qreal energyCost = 0.5;
    QColor _color = QColor(0, 200, 255);
    int timeEnergyDicrease = 8;

    void mutation();

public slots:
    void increaseAge();
    void dicreaseEnergyTime();
};

#endif // ANIMALBASE_H
