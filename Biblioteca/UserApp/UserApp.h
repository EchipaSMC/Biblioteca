#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UserApp.h"

class UserApp : public QMainWindow
{
    Q_OBJECT

public:
    UserApp(QWidget* parent = Q_NULLPTR);

private slots:
    void on_bookSearchBtn_clicked();
    void on_exitBtn_clicked();
    void on_loginBtn_clicked();

private:
    Ui::UserAppClass ui;
};
