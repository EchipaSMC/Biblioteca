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
	ui.listWidget->setSpacing(30);
	nam = new QNetworkAccessManager(this);
	connect(nam, &QNetworkAccessManager::finished, this, &SearchBook::loadImage);
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this, SLOT(onBookListItemDoubleClicked(QListWidgetItem*)));
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
	ui.listWidget->blockSignals(true);
	ui.listWidget->clear();
	ui.listWidget->blockSignals(false);
	std::string searchInput = ui.searchInput->text().toStdString();

	if (searchInput.size())
	{
		user.SetKeyword(searchInput);
		user.SetOption(searchBook);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::vector<Book> searchResult = user.GetSearchedBooks();

		if (searchResult.size())
		{
			titleAndAuthor.clear();
			for (auto& book : searchResult)
			{

				QString imageURL = QString::fromStdString(book.getImgUrl());

				if (imageURL.indexOf("https") == 0)
				{
					imageURL.remove(4, 1);
				}
				titleAndAuthor.push_back(QString(QString::fromStdString(book.getTitle() + " - " + book.getAuthor())));
				QUrl imageNoSecureURL = imageURL;
				QNetworkRequest request(imageNoSecureURL);
				nam->get(request);
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
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
	static int currentTitleAndAuthor = 0;
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage, titleAndAuthor[currentTitleAndAuthor]);
	item->setSizeHint(QSize(100,150));
	ui.listWidget->addItem(item);
	currentTitleAndAuthor++;
	if (currentTitleAndAuthor == titleAndAuthor.size())
		currentTitleAndAuthor -= titleAndAuthor.size();
	reply->deleteLater();
}


void SearchBook::onBookListItemDoubleClicked(QListWidgetItem* item)
{
	std::vector<Book> searchResult = user.GetSearchedBooks();
	for (int i = 0; i < searchResult.size(); i++)
	{
		if (item->text().toStdString() == std::string(searchResult[i].getTitle() + " "+"-"+" " + searchResult[i].getAuthor()))
		{
			user.SetBookId(std::stoi(searchResult[i].getBookId()));
			break;
		}
	}
	user.SetOption(bookDetails);
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	BookDetails currentBook = user.GetBookDetails();
	SelectedBookDetails* bookDetails = new SelectedBookDetails;

	bookDetails->SetAuthor(currentBook.GetAuthor());
	//bookDetails->SetISBN(currentBook.);
	bookDetails->SetRating(std::to_string(currentBook.GetAverageRating()));
	//bookDetails.securrentBook.GetLanguageCode());
	bookDetails->SetTitle(currentBook.GetTitle());
	bookDetails->LoadImageFromURL(currentBook.GetImageUrl());
	bookDetails->show();
}

SearchBook::~SearchBook()
{
	delete nam;
}

std::string SearchBook::GetSearchInput()
{
	return userSearchInput;
}
