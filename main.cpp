#include <QApplication>

#include "presets.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Presets w;
    w.show();

    return a.exec();
}
