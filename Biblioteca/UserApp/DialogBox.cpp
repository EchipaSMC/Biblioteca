#include "DialogBox.h"

DialogBox::DialogBox(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

DialogBox::~DialogBox()
{
}

void DialogBox::on_okBtn_clicked() {
	close();
}

void DialogBox::SetMessage(std::string message)
{
	ui.outputMessage->setText(QString::fromStdString(message));
}
