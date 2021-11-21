#include "SearchBook.h"
#include "UserApp.h"
#include "Login.h"

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
	/*QWidget* bookSearchResultWidget = new bookSearchResult;
	bookSearchResultWidget->show();
	close();*/
}

void SearchBook::on_mainMenuBtn_clicked() {
	QWidget* userAppWidget = new UserApp;
	userAppWidget->show();
	close();
}

SearchBook::~SearchBook()
{
}
