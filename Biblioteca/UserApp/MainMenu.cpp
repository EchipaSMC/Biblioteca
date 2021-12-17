#include "MainMenu.h"
#include "BorrowedBooksList.h"

MainMenu::MainMenu(QWidget* parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
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
	if (user.GetUsername().empty() || user.GetPassword().empty())
	{
		QtMessageBox* warningMessage = new QtMessageBox;
		warningMessage->SetMessage("At least one of the fields is empty!");
		warningMessage->show();
	}
	else
	{
		user.SetOption(loginUser);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		if (user.GetServerError())
		{

			ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), false);
			ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.borrowedBookList), true);
			ui.tabWidget->setCurrentWidget(ui.borrowedBookList);
			ui.borrowedBookList->loadBooks();
		}
		else
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("Your credentials are wrong!");
			warningMessage->show();
		}
	}
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