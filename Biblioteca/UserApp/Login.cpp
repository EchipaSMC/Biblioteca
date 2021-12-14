#include "Login.h"
#include "MainMenu.h"
#include "QtMessageBox.h"

Login::Login(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void Login::on_registerBtn_clicked()
{
	QString usernameInput = ui.usernameInput->text();
	QString passwordInput = ui.passwordInput->text();
	user.SetUsername(usernameInput.toStdString());
	user.SetPassword(passwordInput.toStdString());
	user.SetOption(registerUser);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Login::on_loginBtn_clicked() 
{
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
		QtMessageBox* warningMessage = new QtMessageBox;
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