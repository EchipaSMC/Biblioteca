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
	QString imageURL= QString::fromStdString(message);
	if (imageURL.indexOf("https") == 0)
	{
		imageURL.remove(4, 1);
	}
	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &SelectedBookDetails::loadImage);

	QUrl imageNoSecureURL = imageURL;
	QNetworkRequest request(imageNoSecureURL);
	nam->get(request);
}

void SelectedBookDetails::SetAuthor(std::string author)
{
	ui.bookAuthor->setText(QString::fromStdString(author));
}

void SelectedBookDetails::SetRating(std::string rating)
{
	ui.bookRating->setText(QString::fromStdString(rating));
}

void SelectedBookDetails::SetTags(std::string tags)
{
	ui.bookRating->setText(QString::fromStdString(tags));
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
