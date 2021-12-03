#include "SearchBook.h"
#include "UserApp.h"
#include "Login.h"
#include "DialogBox.h"
#include "Book.h"

SearchBook::SearchBook(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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

		if (true /*searchResult.size()*/)
		{
			//for each (Book book in searchResult)
			//{
			//ui.listWidget->addItem(book.getPictureLink());
			//std::string listItem = book.getTitle() + "     " + book.getAuthor();
			ui.listWidget->addItem("Poza");
			ui.listWidget->addItem("Titlu autor");
			//}
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

SearchBook::~SearchBook()
{
}

std::string SearchBook::GetSearchInput()
{
	return userSearchInput;
}
