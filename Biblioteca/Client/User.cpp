#define _CRT_SECURE_NO_WARNINGS
#include "User.h"

User::User()
{
	this->username = "\0";
	time_t now = time(0);
	whenBorrowed = localtime(&now);
	this->returningDay = "\0";
}

User::~User()
{
	delete[] whenBorrowed;
}

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

//tm* User::GetReturnDate()
//{
//	return this->whenBorrowed;
//}

void User::ShowBorrowedBooks()
{
	std::cout << "User :" << this->username << "borrowed next books: " << std::endl;
	for (auto& elem : this->borrowedBooks)
	{
		std::cout << elem.getBookID() << ". " << elem.getTitle() << " - " << returningDay << std::endl;
		std::cout << "Do you want to prolong the returning date?(y/n)";
		char opt;
		std::cin >> opt;
		if (opt == 'y' || opt == 'Y')
		{
			std::cout << "Please input the number of days:";
			int days;
			std::cin >> days;
			ProlongBorrowDate(whenBorrowed, days);
		}
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

void User::ProlongBorrowDate(tm* retDate, int days)
{
	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(retDate) + (days * one_day);

	*retDate = *localtime(&date_seconds);
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

void User::bookReturn()
{
	ShowBorrowedBooks();
	for (auto elem : borrowedBooks)
	{
		std::cout << "Select?(y/n)";
		char opt;
		std::cin >> opt;

		if (opt == 'y' || opt == 'Y') {
			borrowedBooks.remove(elem);
			std::cout << "You have returned the book succesfully. The book is now available in library.";
			elem.setIfBorrow(opt);
			returningDay = '\0';
		}
	}
}

void User::BookReturnSpecific(int IdBook)
{
	for (auto elem : borrowedBooks)
	{
		if (IdBook == elem.getBookID())
		{
			borrowedBooks.remove(elem);
			std::cout << "You have returned the book succesfully. The book is now available in library.";
			//elem.setIfBorrow(opt);
			returningDay = '\0';
		}
	}
}

void User::ReadBook()
{
	ShowBorrowedBooks();
	std::cout << "Input the id of the book you want to read: ";
	int IdBook;
	std::cin >> IdBook;
	for (auto elem : borrowedBooks)
	{
		if (IdBook == elem.getBookID())
		{
			//afisare continut carte
			break;
		}
	}
	char opt, opt2;
	std::cout << "Have you finished the book?(y/n)";
	std::cin >> opt;
	if (opt == 'y' || opt == 'Y')
	{
		std::cout << "Do you want to return the book?(y/n)";
		std::cin >> opt2;
		if (opt2 == 'y' || opt2 == 'Y')
		{
			BookReturnSpecific(IdBook);
		}
	}
}


void User::LoginRegisterMenu()
{
	std::cout << "Are you already registered?(y/n)";
	char opt;
	std::cin >> opt;
	while (opt != 'y' || opt != 'Y' || opt != ' n' || opt != 'N')
	{
		std::cout << "Invalid option, please repeat.";
		std::cin >> opt;
	}
	if (opt == 'y' || opt == 'Y')
	{
		LoginMenu();
	}
	else if (opt == 'n' || opt == 'N')
	{
		RegisterMenu();
	}
}


//1 casuta user
//1 casuta parola
//1 casuta confirm password
//1 functie verificare parola + confirm parola
//functie afisare meniu
//selectare optiune 
//-> ai deja cont? -> logare 
// -> inregistrare cont
//in functie de optiune mergi pe ramura specifica
// functie inregistrare cont
//-----------------------------------------
//Login/register menu : opt:da/nu -> loginmenu/ registermenu 
//loginmenu ->  show menu

