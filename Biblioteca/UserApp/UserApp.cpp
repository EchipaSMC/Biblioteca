#include "UserApp.h"
#include "SearchBook.h"
#include "Login.h"

UserApp::UserApp(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void UserApp::on_exitBtn_clicked() {
    close();
}

void UserApp::on_loginBtn_clicked()
{
    QWidget* loginWidget = new Login;
    loginWidget->show();
    close();
}

void UserApp::on_bookSearchBtn_clicked()
{
    QWidget* searchBookWidget = new SearchBook;
    searchBookWidget->show();
    close();
}
