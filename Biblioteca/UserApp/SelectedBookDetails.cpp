#include "SelectedBookDetails.h"

SelectedBookDetails::SelectedBookDetails(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

SelectedBookDetails::~SelectedBookDetails()
{
}

void SelectedBookDetails::SetTitle(std::string message)
{
	ui.bookTitle->setText(QString::fromStdString(message));
}

void SelectedBookDetails::LoadImageFromURL(std::string message)
{
	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &SelectedBookDetails::loadImage);

	QUrl imageNoSecureURL = QString::fromStdString(message);
	QNetworkRequest request(imageNoSecureURL);
	nam->get(request);
}

void SelectedBookDetails::loadImage(QNetworkReply* reply) 
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
