#include <QGraphicsView>
#include <QIcon>
#include <QTimer>

#include "processing.h"
#include "presets.h"


Presets::Presets(QWidget *parent) :QMainWindow(parent),

    // Установка стартовых параметров
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this)),
    game(new Processing(*scene, this))

{
    // Установка параметров
    setCentralWidget(view);
    setFixedSize(700,700);
    setWindowIcon(QIcon(":/images/logo snake.jpg"));
    sizeScene();
    backgroundScene();

    QTimer::singleShot(0,this,SLOT(tuningWindow()));
}

Presets::~Presets()
{

}

void Presets::sizeScene() // Эта функция отвечает за масштаб игрового поля
{
    scene->setSceneRect(-100, -100, 200, 200);
}

void Presets::tuningWindow() // Эта функция задает стиль отображения виджета
{
    view->fitInView(scene->sceneRect(),Qt::IgnoreAspectRatio);
}

void Presets::backgroundScene() // Эта функция отвечает за графические параметры игрового поля
{
    QPixmap bg(600, 600);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::black));
    p.drawRect(0, 0, 600, 600);
    view->setBackgroundBrush(bg);
}

void Presets::newGame() // Эта функция отвечает за создание новой игры
{
    QTimer::singleShot(0, game, SLOT(gameOver()));
}
