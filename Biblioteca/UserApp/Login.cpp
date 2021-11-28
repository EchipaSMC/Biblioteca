#include "Login.h"
#include "DialogBox.h"
#include "MainMenu.h"

Login::Login(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void Login::on_loginBtn_clicked() {
	QString usernameInput = ui.usernameInput->text();
	QString passwordInput = ui.passwordInput->text();

	std::string username = usernameInput.toStdString();
	std::string password = usernameInput.toStdString();

	if (true)
	{
		close();
	}

	else
	{
		DialogBox* warningMessage = new DialogBox;
		warningMessage->SetMessage("Your credentials are wrong!");
		warningMessage->show();
	}
}

void Login::on_exitBtn_clicked()
{
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