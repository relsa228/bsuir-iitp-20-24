#include "Forms/loginform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogInForm w;
    w.show();
    return a.exec();
}
