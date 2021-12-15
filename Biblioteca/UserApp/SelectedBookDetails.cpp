#include "SelectedBookDetails.h"
#include "User.h"
#include "QtMessageBox.h"

SelectedBookDetails::SelectedBookDetails(Book book, BookDetails bookDetails, QWidget* parent)
	: QWidget(parent),
	book(book),
	bookDetails(bookDetails)
{
	ui.setupUi(this);
	ui.bookAuthor->setText(QString::fromStdString(book.getAuthor()));
	ui.bookISBN->setText(QString::fromStdString(book.getIsbn()));
	ui.bookTitle->setText(QString::fromStdString(book.getTitle()));
	std::string averageRating = std::to_string(bookDetails.GetAverageRating());
	auto it = std::find(averageRating.begin(), averageRating.end(), '.');
	averageRating.erase(it+3,averageRating.end());
	ui.bookRating->setText(QString::fromStdString(averageRating+ "/5"));
	ui.bookLanguage->setText(QString::fromStdString(bookDetails.GetLanguageCode()));
	ui.bookTags->setText(QString::fromStdString(bookDetails.GetTags()));
	//ui.bookTags->updateGeometry();
	ui.bookTags->setWordWrap(true);
	ui.bookTags->setFixedSize(QSize(269, 81));
	QString imageURL = QString::fromStdString(bookDetails.GetImageUrl());
	if (imageURL.indexOf("https") == 0)
	{
		imageURL.remove(4, 1);
	}
	QNetworkAccessManager* nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &SelectedBookDetails::loadImage);

	QUrl imageNoSecureURL = imageURL;
	QNetworkRequest request(imageNoSecureURL);
	nam->get(request);
	setAttribute(Qt::WA_DeleteOnClose);
}

SelectedBookDetails::~SelectedBookDetails()
{
}

void SelectedBookDetails::on_borrowBtn_clicked()
{
	if (user.GetLoginStatus())
	{
		user.SetOption(borrowBook);
		user.SetBookId(std::stoi(book.getBookId()));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (user.GetServerError())
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("You already borrowed this book!");
			warningMessage->show();
		}
		else
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("You have borrowed the book.\nPlease return it in 2 weeks.");
			warningMessage->show();
		}
	}
	else
	{
		QtMessageBox* warningMessage = new QtMessageBox;
		warningMessage->SetMessage("You are not logged in!");
		warningMessage->show();
	}
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
