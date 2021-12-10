#pragma once

#include <QWidget>
#include "ui_BorrowedBooksList.h"

class BorrowedBooksList : public QWidget
{
	Q_OBJECT

public:
	BorrowedBooksList(QWidget *parent = Q_NULLPTR);
	~BorrowedBooksList();

private:
	Ui::BorrowedBooksList ui;
};
