#pragma once

#include <QWidget>
#include "ui_MainMenu.h"

class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget *parent = Q_NULLPTR);
	~MainMenu();

private slots:
	void on_loginBtn_clicked();
	void on_logOutBtn_clicked();
	void on_borrowBookBtn_clicked();
	void on_borrowedBooksBtn_clicked();
	void on_retunBookBtn_clicked();
	void on_searchBtn_clicked();

private:
	Ui::MainMenu ui;
};
