#include "PasswordChange.h"
#include "User.h"
#include "QtMessageBox.h"

PasswordChange::PasswordChange(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

PasswordChange::~PasswordChange()
{

}

void PasswordChange::on_passwordChangeBtn_clicked() 
{
	if (ui.oldPasswordInput->text() != QString::fromStdString(user.GetPassword()))
	{
		QtMessageBox* errorMessage=new QtMessageBox;
		errorMessage->SetMessage("Old password doesn't match!");
	}
	else
	{
		QString newPassword = ui.newPasswordInput->text();
		QString passwordConfirm = ui.confirmPasswordInput->text();

		if (newPassword == passwordConfirm)
		{
			if (user.PasswordRequirements(newPassword.toStdString()))
			{
				user.SetKeyword(newPassword.toStdString());
				user.SetOption(changePassword);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				close();
			}
		}
		else
		{
			QtMessageBox* errorMessage = new QtMessageBox;
			errorMessage->SetMessage("New password and confirm passwords don't match!");
		}
	}
	user.SetOption(changePassword);

	close();
}
