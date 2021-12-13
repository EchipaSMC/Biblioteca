#pragma once

#include <QWidget>
#include "ui_SelectedBookDetails.h"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <qimagereader.h>

class SelectedBookDetails : public QWidget
{
	Q_OBJECT

public:
	SelectedBookDetails(QWidget *parent = Q_NULLPTR);
	~SelectedBookDetails();

	void SetTitle(std::string message);
	void LoadImageFromURL(std::string message);
	void SetAuthor(std::string author);
	void SetRating(std::string rating);
	void SetISBN(std::string isbn);
	void SetTags(std::string tags);

private slots:
	void loadImage(QNetworkReply* reply);

private:
	Ui::SelectedBookDetails ui;
};
