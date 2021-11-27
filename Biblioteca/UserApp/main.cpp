#include "UserApp.h"
#include <QtWidgets/QApplication>
#include "MainMenu.h"
#include "Login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu gui;
    gui.show();
    Login login;
    login.show();
    return a.exec();
}
