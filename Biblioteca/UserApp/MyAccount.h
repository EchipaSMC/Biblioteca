#pragma once

#include <QWidget>
#include "ui_MyAccount.h"

class MyAccount : public QWidget
{
	Q_OBJECT

public:
	MyAccount(QWidget *parent = Q_NULLPTR);
	~MyAccount();
		
private:
	Ui::MyAccount ui;
};
