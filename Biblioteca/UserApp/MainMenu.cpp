#include "MainMenu.h"
#include "DialogBox.h"

MainMenu::MainMenu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tabWidget->setCurrentWidget(ui.searchBook);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.myAccount), false);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.searchResult), false);
}

MainMenu::~MainMenu()
{
}

void MainMenu::on_loginBtn_clicked() {
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), false);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.myAccount), true);
	ui.tabWidget->setCurrentWidget(ui.myAccount);
	//use user data
}

void MainMenu::on_logOutBtn_clicked(){
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.login), true);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.myAccount), false);
	ui.tabWidget->setCurrentWidget(ui.login);
	//delete last user data
}

void MainMenu::on_borrowBookBtn_clicked()
{
}

void MainMenu::on_borrowedBooksBtn_clicked()
{
}

void MainMenu::on_retunBookBtn_clicked()
{
}

//void MainMenu::on_searchBtn_clicked()
//{
//	SearchBook currentWidget = ui.tabWidget->widget(ui.tabWidget->indexOf(ui.searchBook));
//	std::string searchInputText = currentWidget.GetSearchInput();
//
//	if (searchInputText.size()>0)
//	{
//		ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.searchResult), true);
//		ui.tabWidget->setCurrentWidget(ui.searchResult);
//	}
//	else
//	{
//		DialogBox* warningMessage = new DialogBox;
//		warningMessage->SetMessage("No search input given!");
//		warningMessage->show();
//	}
//	
//}
