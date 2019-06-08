#ifndef PRESETS_H
#define PRESETS_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;

class Processing;

class Presets : public QMainWindow
{
    Q_OBJECT
public:
    Presets (QWidget *parent = 0);
    ~Presets();

private slots:
    void tuningWindow();
    void newGame();

private:
    void sizeScene();
    void backgroundScene();

    QGraphicsScene *scene;
    QGraphicsView *view;
    Processing *game;
};

#endif // PRESETS_H
