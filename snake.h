#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QRectF>

class Processing;

class Snake : public QGraphicsItem
{
public:

    // перечисление для направления змейки
    enum Direction
    {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(Processing & controller);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    Direction RMoveDirection();
    void setMoveDirection(Direction direction);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);


private:
    void advance(int step);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void handleCollisions();

    QList<QPointF> tail;
    QPointF head;
    Direction moveDirection;
    Processing &controller;
    int growing;
    int speed;
    int tickCounter;
    bool povorot=true;
};

#endif // SNAKE_H
