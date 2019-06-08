#ifndef PROCESSING_H
#define PROCESSING_H

#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;

class Processing : public QObject
{
    Q_OBJECT
public:
    Processing(QGraphicsScene &scene, QObject *parent = 0);
    void snakeEatFood(Food *food);
    void cannibalism();

public slots:
    void esume();
    void gameOver();

private:
    ~Processing();
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();
    bool eventFilter(QObject *object, QEvent *event);

    QTimer timer;
    QGraphicsScene &scene;
    Snake *snake;
    bool Pause;
};

#endif // PROCESSING_H
