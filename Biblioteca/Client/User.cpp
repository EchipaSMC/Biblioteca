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

User::User(const User& user)
{
	this->username = user.username;
	this->borrowedBooks = user.borrowedBooks;
}

std::string User::GetUsername() const
{
	return username;
}

std::vector<Book> User::GetBorrowedBooks() const
{
	return borrowedBooks;
}

void User::ShowBorrowedBooks(const std::string& user, const std::vector<Book>& books)
{
	std::cout << "Userul :" << user << "a imprumutat urmatoarele carti: " << std::endl;
	for (auto& elem : books)
	{
		std::cout << elem.getBookID() << " " << elem.getTitle() << std::endl;
	}
}
