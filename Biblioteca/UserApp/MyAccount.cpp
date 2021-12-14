#include "MyAccount.h"

MyAccount::MyAccount(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

MyAccount::~MyAccount()
{
}
