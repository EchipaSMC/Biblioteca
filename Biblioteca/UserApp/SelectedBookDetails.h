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

private slots:
	void loadImage(QNetworkReply* reply);

private:
	Ui::SelectedBookDetails ui;
};
