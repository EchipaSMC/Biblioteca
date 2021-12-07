#include "SearchBook.h"
#include "UserApp.h"
#include "Login.h"
#include "DialogBox.h"
#include "Book.h"

SearchBook::SearchBook(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.listWidget->setViewMode(QListWidget::IconMode);
	ui.listWidget->setIconSize(QSize(200, 150));
	ui.listWidget->setResizeMode(QListWidget::Adjust);
	ui.listWidget->setSpacing(20);
}

void SearchBook::on_exitBtn_clicked() {
	close();
}

void SearchBook::on_loginBtn_clicked()
{
	QWidget* loginWidget = new Login;
	loginWidget->show();
	close();
}

void SearchBook::on_searchBtn_clicked()
{
	std::string searchInput = ui.searchInput->text().toStdString();

	if (searchInput.size())
	{
		std::vector<Book> searchResult; //= send input to server and receive a vector (of books) containing all the books matching the search input

		if (true /*searchResult.size()*/)
		{
			QNetworkAccessManager* nam = new QNetworkAccessManager(this);
			connect(nam, &QNetworkAccessManager::finished, this, &SearchBook::loadImage);

			for each (Book book in searchResult)
			{
				QString imageURL = QString::fromStdString(book.getImgUrl());

				if (imageURL.indexOf("https") == 0)
				{
					imageURL.remove(4, 1);
				}

				titleAndAuthor = QString::fromStdString(book.getTitle() + " " + book.getAuthor());

				QUrl imageNoSecureURL = imageURL;
				QNetworkRequest request(imageNoSecureURL);
				nam->get(request);
			}
		}
		else
		{
			DialogBox* warningMessage = new DialogBox;
			warningMessage->SetMessage("No matches found!");
			warningMessage->show();
		}
	}
	else
	{
		DialogBox* warningMessage = new DialogBox;
		warningMessage->SetMessage("No search input given!");
		warningMessage->show();
	}
}

void SearchBook::loadImage(QNetworkReply* reply)
{
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	//ui.label->setPixmap(bookCoverImage);
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage, titleAndAuthor);
	ui.listWidget->addItem(item);
}

SearchBook::~SearchBook()
{
}

std::string SearchBook::GetSearchInput()
{
	return userSearchInput;
}
