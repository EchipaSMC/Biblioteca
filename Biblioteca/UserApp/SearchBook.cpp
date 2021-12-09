#include "SearchBook.h"
#include "UserApp.h"
#include "Login.h"
#include "QtMessageBox.h"
#include "SelectedBookDetails.h"

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
	ui.listWidget->clear();
	std::string searchInput = ui.searchInput->text().toStdString();

	if (searchInput.size())
	{
		//user.SearchBooks(searchInput);
		std::vector<Book> searchResult;// = user.GetSearchedBooks(); //= send input to server and receive a vector (of books) containing all the books matching the search input

		if (true/*searchResult.size()*/)
		{
			Book book = Book();
			book.setImgUrl("https://images.gr-assets.com/books/1447303603m/2767052.jpg");
			book.setAuthor("Exemplu Autor");
			book.setIsbn("Ex12334123");
			book.setTitle("Exemplu Titlu");
			searchResult.push_back(book);
			searchResult.push_back(book);
			searchResult.push_back(book);
			searchResult.push_back(book);

			QNetworkAccessManager* nam = new QNetworkAccessManager(this);
			connect(nam, &QNetworkAccessManager::finished, this, &SearchBook::loadImage);

			connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
				this, SLOT(onBookListItemDoubleClicked(QListWidgetItem*)));

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
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("No matches found!");
			warningMessage->show();
		}
	}
	else
	{
		QtMessageBox* warningMessage = new QtMessageBox;
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

void SearchBook::onBookListItemDoubleClicked(QListWidgetItem* item)
{
	SelectedBookDetails* details = new SelectedBookDetails;
	details->SetTitle(item->text().toStdString());
	details->LoadImageFromURL("http://images.gr-assets.com/books/1447303603m/2767052.jpg");
	details->show();
}

SearchBook::~SearchBook()
{
}

std::string SearchBook::GetSearchInput()
{
	return userSearchInput;
}
