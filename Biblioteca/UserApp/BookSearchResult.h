#pragma once

#include <QWidget>
#include "ui_BookSearchResult.h"

class BookSearchResult : public QWidget
{
	Q_OBJECT

public:
	BookSearchResult(QWidget *parent = Q_NULLPTR);
	~BookSearchResult();

private:
	Ui::BookSearchResult ui;
	
};
