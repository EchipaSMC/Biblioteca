#include "BorrowedBookDetails.h"

BorrowedBookDetails::BorrowedBookDetails(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

BorrowedBookDetails::~BorrowedBookDetails()
{
}

void BorrowedBookDetails::SetTitle(std::string message)
{
	ui.bookTitle->setText(QString::fromStdString(message));
}

void BorrowedBookDetails::LoadImageFromURL(std::string message)
{
	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &BorrowedBookDetails::loadImage);

	QUrl imageNoSecureURL = QString::fromStdString(message);
	QNetworkRequest request(imageNoSecureURL);
	nam->get(request);
}

void BorrowedBookDetails::loadImage(QNetworkReply* reply)
{
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	//ui.label->setPixmap(bookCoverImage);
	ui.bookImage->setPixmap(bookCoverImage);

	int w = ui.bookImage->width();
	int h = ui.bookImage->height();

	// set a scaled pixmap to a w x h window keeping its aspect ratio 
	ui.bookImage->setPixmap(bookCoverImage.scaled(w, h, Qt::KeepAspectRatio));

}
