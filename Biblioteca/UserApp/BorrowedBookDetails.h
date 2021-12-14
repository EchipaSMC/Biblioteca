#pragma once

#include <QWidget>
#include "ui_BorrowedBookDetails.h"
#include <QtNetwork/qnetworkreply.h>

class BorrowedBookDetails : public QWidget
{
	Q_OBJECT

public:
	BorrowedBookDetails(QWidget *parent = Q_NULLPTR);
	~BorrowedBookDetails();
	void SetTitle(std::string message);
	void SetAuthor(std::string message);
	void SetRating(std::string rating);
	void SetISBN(std::string ISBN);
	void SetLanguage(std::string language);
	void SetTags(std::string tags);
	void LoadImageFromURL(std::string message);

private slots:
	void loadImage(QNetworkReply* reply);

private:
	Ui::BorrowedBookDetails ui;
};
