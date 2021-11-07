#include "User.h"

User::User(std::string nickname, std::vector<Book> borrowedB)
{
	this->username = nickname;
	this->borrowedBooks = borrowedB;
}

User::User(const User& user)
{
	this->username = user.username;
	this->borrowedBooks = user.borrowedBooks;
}
