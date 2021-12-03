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
		std::vector<Book> searchResult; //= send input to server and receive a vector containing the books matching the input

		if (searchResult.size())
		{
			for each (Book book in searchResult)
			{
			ui.listWidget->addItem(book.getPictureLink());
			std::string listItem = book.getTitle() + "     " + book.getAuthor();
			QString path = "C/users/stefa/img/ex.jpg";
			QListWidgetItem* item = new QListWidgetItem(QIcon(path), titleAndAuthor);
			ui.listWidget->addItem(item);
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
