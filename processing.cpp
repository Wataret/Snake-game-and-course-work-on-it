#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMessageBox>

#include "processing.h"
#include "food.h"
#include "snake.h"

Processing::Processing(QGraphicsScene &scene, QObject *parent) :

    // Установка стартовых параметров
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    Pause(false)

{
    //Установка параметров
    timer.start(1000/33);
    Food *a1 = new Food(0, -50);
    scene.addItem(a1);
    scene.addItem(snake);
    scene.installEventFilter(this);
    esume();
}

Processing::~Processing()
{
}

void Processing::snakeEatFood(Food *food) //Эта функция отвечает за поедание еды
{
    scene.removeItem(food);
    addNewFood();
}

void Processing::cannibalism() // Эта функция отвечает за вызов окна "Конец игры" при поедание змейки самой себя
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}
void Processing::addNewFood()  // Эта функция отвечает за добавление еды на игровое поле
{
    int x, y;
    do
    {
        x = (int)(qrand() % 200) / 10 - 10;
        y = (int)(qrand() % 200) / 10 - 10;

        x *= 10;
        y *= 10;
    }

    while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));
    Food *food = new Food(x, y);
    scene.addItem(food);
}
void Processing::handleKeyPressed(QKeyEvent *event) // Эта функция отвечает за обработку нажатий клавиш
{
    if (!Pause)
        switch (event->key())
        {
        case Qt::Key_Left:
            snake->setMoveDirection(Snake::MoveLeft);
            break;
        case Qt::Key_Right:
            snake->setMoveDirection(Snake::MoveRight);
            break;
        case Qt::Key_Up:
            snake->setMoveDirection(Snake::MoveUp);
            break;
        case Qt::Key_Down:
            snake->setMoveDirection(Snake::MoveDown);
            break;
        }
    else
        esume();
}

bool Processing::eventFilter(QObject *object, QEvent *event) // Эта функция за считывание нажатия на клавишу
{
    if (event->type() == QEvent::KeyPress)
    {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else
    {
        return QObject::eventFilter(object, event);
    }
}

void Processing::gameOver()  //Эта функция отвечает за создание экрана "Конец игры"
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    if (QMessageBox::Yes == QMessageBox::information(
                NULL,
                tr("Конец игры"), tr("Хотите начать заново ?"),
                QMessageBox::Yes|QMessageBox::No,
                QMessageBox::Yes))
    {
        connect(&timer, SIGNAL(timeout()),
                &scene, SLOT(advance()));
        scene.clear();

        snake = new Snake(*this);
        scene.addItem(snake);
        addNewFood();
    }
    else
    {
        exit(0);
    }
}

void Processing::esume() //Эта функция отвечает за продолжение игры
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
    Pause = false;
}


