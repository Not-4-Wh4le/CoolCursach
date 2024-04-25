#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>


class Food : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Food(QObject *parent = nullptr);
    ~Food();


signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
};


#endif // FOOD_H
