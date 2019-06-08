#include <QPainter>

#include "food.h"
#include "variable.h"

Food::Food(int x,int y) // Эта функция отвечает за установка координат еды
{
    setPos(x,y);
    setData(GD_Type,GO_Food);
}

void Food::paint(QPainter *painter,const QStyleOptionGraphicsItem *,QWidget *) // Эта функция отвечает за отрисовку еды на поле
{
    painter->save();
    painter->drawPixmap(0,0,10,10,QPixmap(":/images/fruit.png"));
    painter->restore();
}

QPainterPath Food::shape() const // Эта функция  возвращает форму этого элемента в виде QPainterPath в локальных координатах.

{
    QPainterPath p;
    p.addEllipse(QPointF(5,5),3,3);
    return p;
}

QRectF Food::boundingRect() const // Эта функция определяет внешние границы элемента и определяется нуждается ли элемент в перерисовке

{
    return QRectF(-10,-10,20,20);
}

