#include "app.h"

#include <QApplication>
#include <QVariant>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App app;
    app.start();

    return a.exec();
}
