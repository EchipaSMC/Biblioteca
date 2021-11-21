#include "Login.h"

Login::Login(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void Login::on_loginBtn_clicked() {
	close();
}

void Login::on_exitBtn_clicked()
{
	close();
}

void Login::on_mainMenuBtn_clicked()
{
	QWidget* userAppWidget = new UserApp;
	userAppWidget->show();
	close();
}

void Login::on_bookSearchBtn_clicked()
{
	QWidget* searchBookWidget = new SearchBook;
	searchBookWidget->show();
	close();
}

Login::~Login()
{
}