#include "regwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RegWindow w;
    w.show();
    return a.exec();
}
