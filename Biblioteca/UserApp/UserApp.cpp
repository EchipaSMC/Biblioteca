#include "UserApp.h"

UserApp::UserApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void UserApp::on_exitBtn_clicked() {
    close();
}

void UserApp::on_bookSearchBtn_clicked()
{
    QWidget* wdg = new QWidget;
    wdg->show();
    this->hide();
}
