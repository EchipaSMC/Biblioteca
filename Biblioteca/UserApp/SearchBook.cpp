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
	disconnect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		this, SLOT(onBookListItemDoubleClicked(QListWidgetItem*)));
	std::string searchInput = ui.searchInput->text().toStdString();

	if (searchInput.size())
	{
		user.SetKeyword(searchInput);
		user.SetOption(searchBook);
		std::this_thread::sleep_for(std::chrono::milliseconds(750));
		std::vector<Book> searchResult = user.GetSearchedBooks();

		if (searchResult.size())
		{
			QNetworkAccessManager* nam = new QNetworkAccessManager(this);
			connect(nam, &QNetworkAccessManager::finished, this, &SearchBook::loadImage);
			connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
				this, SLOT(onBookListItemDoubleClicked(QListWidgetItem*)));
			titleAndAuthor.clear();
			for each (Book bookResult in searchResult)
			{
				
				QString imageURL = QString::fromStdString(bookResult.getImgUrl());

				if (imageURL.indexOf("https") == 0)
				{
					imageURL.remove(4, 1);
				}
				titleAndAuthor.push_back(QString( QString::fromStdString(bookResult.getTitle() + " " + bookResult.getAuthor())));

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
	static int currentTitleAndAuthor = 0;
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	//ui.label->setPixmap(bookCoverImage);
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage, titleAndAuthor[currentTitleAndAuthor]);
	ui.listWidget->addItem(item);
	currentTitleAndAuthor++;
	if (currentTitleAndAuthor == titleAndAuthor.size())
		currentTitleAndAuthor -= titleAndAuthor.size();
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
