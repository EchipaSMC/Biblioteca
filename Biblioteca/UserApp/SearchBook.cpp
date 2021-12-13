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
	/*disconnect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this, SLOT(onBookListItemDoubleClicked(QListWidgetItem*)));*/
	std::string searchInput = ui.searchInput->text().toStdString();

	if (searchInput.size())
	{
		user.SetKeyword(searchInput);
		user.SetOption(searchBook);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::vector<Book> searchResult = user.GetSearchedBooks();

		if (searchResult.size())
		{
			//QNetworkAccessManager* nam = new QNetworkAccessManager(this);
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
	QString first20Characters = QStringRef(&titleAndAuthor[currentTitleAndAuthor], 0, 20).toString() + "...";
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage, first20Characters);
	ui.listWidget->addItem(item);
	currentTitleAndAuthor++;
	if (currentTitleAndAuthor == titleAndAuthor.size())
		currentTitleAndAuthor -= titleAndAuthor.size();
}


void SearchBook::onBookListItemDoubleClicked(QListWidgetItem* item)
{
	std::vector<Book> searchResult = user.GetSearchedBooks();
	for (int i = 0; i < searchResult.size(); i++)
	{
		if (item->text().toStdString() == std::string(searchResult[i].getTitle() + " " + searchResult[i].getAuthor()))
		{
			user.SetBookId(std::stoi(searchResult[i].getBookId()));
			break;
		}
	}
	user.SetOption(bookDetails);
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	BookDetails currentBook = user.GetBookDetails();
	SelectedBookDetails* bookDetails = new SelectedBookDetails;
	bookDetails->SetTitle(item->text().toStdString());
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
