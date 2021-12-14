#include "Login.h"
#include "MainMenu.h"
#include "QtMessageBox.h"

Login::Login(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

void Login::on_registerBtn_clicked()
{
	QString usernameInput = ui.usernameInput->text();
	QString passwordInput = ui.passwordInput->text();
	if(!user.PasswordRequirements(passwordInput.toStdString()))
	{
		QtMessageBox* warningMessage = new QtMessageBox;
		warningMessage->SetMessage("Please choose another password!\nIt needs to have one lowercase letter, one uppercase,\n a digit and a special character!\nIt cannot contain ' .");
		warningMessage->show();
	}
	else
	{
		user.SetUsername(usernameInput.toStdString());
		user.SetPassword(passwordInput.toStdString());
		user.SetOption(registerUser);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (!user.GetServerError())
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("You have been registered! \nYou can now log in!");
			warningMessage->show();
		}
		else
		{
			QtMessageBox* warningMessage = new QtMessageBox;
			warningMessage->SetMessage("There is already a registered user with that username!");
			warningMessage->show();
		}
	}
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