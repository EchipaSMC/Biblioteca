#pragma once

#include <QWidget>
#include "ui_DialogBox.h"

class DialogBox : public QWidget
{
	Q_OBJECT

public:
	DialogBox(QWidget *parent = Q_NULLPTR);
	~DialogBox();
	void SetMessage(std::string message);

private slots:
	void on_okBtn_clicked();

private:
	Ui::DialogBox ui;
};
