#pragma once

#include <QWidget>
#include "ui_SearchBook.h"

class SearchBook : public QWidget
{
	Q_OBJECT

public:
	SearchBook(QWidget* parent = Q_NULLPTR);
	~SearchBook();

private slots:
	void on_exitBtn_clicked();
	void on_loginBtn_clicked();
	void on_searchBtn_clicked();

private:
	Ui::SearchBook ui;
};
