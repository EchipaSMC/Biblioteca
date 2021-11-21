#pragma once

#include <QWidget>
#include "ui_Login.h"
#include "SearchBook.h"
#include "UserApp.h"

class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();

private slots:
	void on_loginBtn_clicked();
	void on_exitBtn_clicked();
	void on_mainMenuBtn_clicked();
	void on_bookSearchBtn_clicked();

private:
	Ui::Login ui;
};
