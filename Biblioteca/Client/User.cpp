#define _CRT_SECURE_NO_WARNINGS
#include "User.h"

User::User(std::string nickname, std::list<Book> borrowedB)
{
	this->username = nickname;
	this->borrowedBooks = borrowedB;
	time_t now = time(0);
	this->whenBorrowed = localtime(&now);
}

User::User(const User& user)
{
	this->username = user.username;
	this->borrowedBooks = user.borrowedBooks;
	this->whenBorrowed = user.whenBorrowed;
}

std::string User::GetUsername() const
{
	return username;
}

std::list<Book> User::GetBorrowedBooks() const
{
	return borrowedBooks;
}

void User::ShowBorrowedBooks(const User& user)
{
	std::cout << "User :" << user.username << "borrowed next books: " << std::endl;
	for (auto& elem : user.borrowedBooks)
	{
		std::cout << elem.getBookID() << ". " << elem.getTitle() <<" - " << returningDay << std::endl;
	}
}

void User::Borrowing(std::string& keyword)
{
	Book b;
	if (search(keyword) == true)
	{
		borrowedBooks.push_back(b);
		returningDate(whenBorrowed, 14);
		returningDay = asctime(whenBorrowed);
	}
}


void User::returningDate(tm* currentDate, int days)
{
	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(currentDate) + (days * one_day);

	*currentDate = *localtime(&date_seconds); 
}

bool User::search(std::string searchKeyword)
{
	InvertedIndex index;
	if (index.getDictionary().find(searchKeyword) == index.getDictionary().end())
	{
		std::cout << "Title/author not found.";
		return false;
	}

	int size = int(index.getDictionary()[searchKeyword].size());
	for (int i = 0; i < size; i++)
	{
		std::cout << i + 1;
		std::cout << "\n  Line: " << index.getDictionary()[searchKeyword][i].line << std::endl;
		std::cout << "  Index: " << index.getDictionary()[searchKeyword][i].index << std::endl;
	}
	return true;
}