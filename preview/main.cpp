#include "preview.h"

#include <QApplication>
#include <QVariant>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Preview preview;
    preview.start();

    return a.exec();
}
