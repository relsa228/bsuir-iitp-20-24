#include "taskwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskWindow w;
    w.show();
    return a.exec();
}
