#include "UserApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserApp w;
    w.show();
    return a.exec();
}
