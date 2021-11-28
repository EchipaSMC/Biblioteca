#include "SearchBook.h"
#include "UserApp.h"
#include "Login.h"
#include "DialogBox.h"

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
	QString searchInput = ui.searchInput->text();
	std::string search = searchInput.toStdString();

	if (search.size())
	{
		/*QWidget* bookSearchResultWidget = new bookSearchResult;
	bookSearchResultWidget->show();
	*/
		close();
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
