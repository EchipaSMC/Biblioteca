#pragma once

#include <QWidget>
#include "ui_MyAccount.h"

class MyAccount : public QWidget
{
	Q_OBJECT

public:
	MyAccount(QWidget *parent = Q_NULLPTR);
	~MyAccount();

private slots:
	void on_borrowBookBtn_clicked();
	void on_borrowedBooksBtn_clicked();
	void on_logOutBtn_clicked();
	void on_retunBookBtn_clicked();
		
private:
	Ui::MyAccount ui;
};
