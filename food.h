#ifndef FOOD_H
#define FOOD_H

#include <QGraphicsItem>

class Food : public QGraphicsItem
{
public:
    Food(int x, int y);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *);
};

#endif // FOOD_H
