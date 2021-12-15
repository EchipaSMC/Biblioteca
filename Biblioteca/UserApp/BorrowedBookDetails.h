#pragma once

#include <QWidget>
#include "ui_BorrowedBookDetails.h"
#include <QtNetwork/qnetworkreply.h>
#include "BorrowedBooks.h"
#include "BookDetails.h"

class BorrowedBookDetails : public QWidget
{
	Q_OBJECT

public:
	BorrowedBookDetails(BorrowedBooks borrowedBook, BookDetails bookDetails, QWidget* parent = Q_NULLPTR);
	~BorrowedBookDetails();

private slots:
	void loadImage(QNetworkReply* reply);

private:
	BorrowedBooks borrowedBook;
	BookDetails bookDetails;
	Ui::BorrowedBookDetails ui;
};
