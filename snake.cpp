#include <QPainter>

#include "snake.h"
#include "processing.h"
#include "food.h"
#include "variable.h"

Snake::Snake(Processing &controller) :

    // Установка стартовых параметров
    head(0,0),
    growing(2),
    speed(4),
    moveDirection(NoMove),
    controller(controller)

{

}

QRectF Snake::boundingRect() const // Эта функция отвечает за увелечение змейки
{
    int minX = head.x();
    int minY = head.y();
    int maxX = head.x();
    int maxY = head.y();

    foreach (QPointF p, tail) // foreach несете функцию перебора всех элементов контейнера
    {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));
    QRectF bound = QRectF(tl.x(),tl.y(),br.x() - tl.x() + 10,br.y() - tl.y() + 10);
    return bound;
}


QPainterPath Snake::shape() const // Эта функция возвращает форму этого элемента в виде QPainterPath в локальных координатах.
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(QRectF(0,0,10,10));

    foreach (QPointF p, tail)
    {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(),10,10));
    }
    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) // Эта функция отвечает за отрисовку змейки на поле
{
    painter->save();
    painter->fillPath(shape(),Qt::darkGreen);

    if (povorot==true)
    {
        painter->drawPixmap(0,0,10,10,QPixmap(":/images/0 grade.png"));
    }
    else
    {
        painter->drawPixmap(0,0,10,10,QPixmap(":/images/180 grade.png"));
    }
    painter->restore();
}

void Snake::setMoveDirection(Direction direction) // Эта функция устанавливает направление змейки
{
    if (moveDirection == MoveLeft && direction == MoveRight)
        return;
    if (moveDirection == MoveRight && direction == MoveLeft)
        return;
    if (moveDirection == MoveUp && direction == MoveDown)
        return;
    if (moveDirection == MoveDown && direction == MoveUp)
        return;
    moveDirection = direction;
}

Snake::Direction Snake::RMoveDirection() // Эта функция возвращает направление змейки
{
    return moveDirection;
}

void Snake::moveLeft() // Эта функция отвечает за поворот змейки в левую сторону
{
    head.rx() -= 10;
    if (head.rx() < -100)
    {
        head.rx() = 90;
    }
    povorot=false;
}

void Snake::moveRight() // Эта функция отвечает за поворот змейки в праву сторону
{
    head.rx() += 10;
    if (head.rx() >= 100)
    {
        head.rx() = -100;
    }
    povorot=false;
}

void Snake::moveUp() // Эта функция отвечает за поворот змейки в верхнюю сторону
{
    head.ry()-=10;
    if (head.ry()<-100)
    {
        head.ry()=90;
    }
    povorot=true;
}

void Snake::moveDown() // Эта функция отвечает за поворот змейки в нижнюю сторону
{
    head.ry() += 10;
    if (head.ry() >= 100)
    {
        head.ry() = -100;
    }
    povorot=true;
}

void Snake::advance(int step) // Эта функция отвечает за обновлении положение змейки  на игровом поле
{
    if (!step)
    {
        return;
    }
    if (tickCounter++ % speed != 0)
    {
        return;
    }
    if (moveDirection == NoMove)
    {
        return;
    }

    if (growing > 0)
    {
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else
    {
        tail.removeFirst();
        tail << head;
    }

    switch (moveDirection)
    {
    case MoveLeft:
        moveLeft();
        break;
    case MoveRight:
        moveRight();
        break;
    case MoveUp:
        moveUp();
        break;
    case MoveDown:
        moveDown();
        break;
    }
    setPos(head);
    handleCollisions();
}

void Snake::handleCollisions() //  Эта функция отвечает за обработку столкновения змейки с самой собой и едой
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions)
    {
        if (collidingItem->data(GD_Type) == GO_Food)
        {
            controller.snakeEatFood((Food *)collidingItem);
            growing += 1;
        }
    }

    if (tail.contains(head))
    {
        controller.cannibalism();
    }
}
