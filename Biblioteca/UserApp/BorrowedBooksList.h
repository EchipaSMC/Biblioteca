#pragma once

#include <QWidget>
#include "ui_BorrowedBooksList.h"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <qimagereader.h>

class BorrowedBooksList : public QWidget
{
	Q_OBJECT

public:
	BorrowedBooksList(QWidget *parent = Q_NULLPTR);
	~BorrowedBooksList();

private slots:
	void onBorrowedBookListItemDoubleClicked(QListWidgetItem* item);
	void loadImage(QNetworkReply* reply);

private:
	Ui::BorrowedBooksList ui;
	QString titleAndAuthor;
};
