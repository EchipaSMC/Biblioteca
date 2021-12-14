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

void BorrowedBookDetails::SetAuthor(std::string message)
{
	ui.bookAuthor->setText(QString::fromStdString(message));
}

void BorrowedBookDetails::SetRating(std::string rating)
{
	ui.bookRating->setText(QString::fromStdString(rating+"/5.0"));
}

void BorrowedBookDetails::SetISBN(std::string ISBN)
{
	ui.bookISBN->setText(QString::fromStdString(ISBN));
}

void BorrowedBookDetails::SetLanguage(std::string language)
{
	ui.bookLanguage->setText(QString::fromStdString(language));
}

void BorrowedBookDetails::SetTags(std::string tags)
{
	ui.bookTags->setText(QString::fromStdString(tags));
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
