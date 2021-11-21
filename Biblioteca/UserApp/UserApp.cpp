#include "UserApp.h"
#include "SearchBook.h"

UserApp::UserApp(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void UserApp::on_exitBtn_clicked() {
    close();
}

void UserApp::on_bookSearchBtn_clicked()
{
    QWidget* searchBookWidget = new SearchBook;
    searchBookWidget->show();
    close();
}
