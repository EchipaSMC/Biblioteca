#include "MainMenu.h"
#include "BorrowedBooksList.h"

MainMenu::MainMenu(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tabWidget->setCurrentWidget(ui.searchBook);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.borrowedBookList), false);
	//ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.searchResult), false);
}

MainMenu::~MainMenu()
{
}

void MainMenu::DeleteUserLogout()
{
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), true);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.borrowedBookList), false);
	emit on_yesBtn_clicked();
}

void MainMenu::on_loginBtn_clicked() {
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), false);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.borrowedBookList), true);
	ui.tabWidget->setCurrentWidget(ui.borrowedBookList);
	ui.borrowedBookList->loadBooks();
}

void MainMenu::on_logOutBtn_clicked() 
{
	user.SetOption(logout);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), true);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.borrowedBookList), false);
}

void MainMenu::on_deleteUserBtn_clicked()
{
	user.SetOption(deleteAccount);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), true);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.borrowedBookList), false);
}