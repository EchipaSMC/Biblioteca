#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.tabWidget->setCurrentWidget(ui.searchBook);
	ui.tabWidget->setTabVisible(ui.tabWidget->indexOf(ui.myAccount), false);
}

MainMenu::~MainMenu()
{
}
