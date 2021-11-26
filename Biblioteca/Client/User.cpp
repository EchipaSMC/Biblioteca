#define _CRT_SECURE_NO_WARNINGS
#include "User.h"

User::User()
{
	this->username = "\0";
	time_t now = time(0);
	whenBorrowed = localtime(&now);
	this->returningDay = "\0";
	this->password = '\0';
}

User::~User()
{
	delete[] whenBorrowed;
}

User::User(std::string nickname, std::vector<Book> borrowedB, std::string password)
{
	this->username = nickname;
	this->borrowedBooks = borrowedB;
	time_t now = time(0);
	this->whenBorrowed = localtime(&now);
	this->password = password;
}

User::User(std::string username, std::string password)
{
	this->username = username;
	this->password = password;
	time_t now = time(0);
	this->whenBorrowed = localtime(&now);
	this->returningDay = "\0";
	this->borrowedBooks.resize(0);
}

User::User(const std::string& data)
{
	std::stringstream iss(data);
	char character = ' ';

	std::vector<std::string> vecData;
	std::string detailedData;
	while (std::getline(iss, detailedData, character))
	{
		vecData.push_back(detailedData);
	}

	this->username = vecData[0];
	this->password = vecData[1];

	time_t now = time(0);
	whenBorrowed = localtime(&now);
	this->returningDay = "\0";
	this->borrowedBooks.resize(0);
}

User::User(const User& user)
{
	this->username = user.username;
	this->borrowedBooks = user.borrowedBooks;
	this->whenBorrowed = user.whenBorrowed;
	this->password = user.password;
}

std::string User::GetUsername() const
{
	return username;
}

std::vector<Book> User::GetBorrowedBooks() const
{
	return borrowedBooks;
}

//tm* User::GetReturnDate()
//{
//	return this->whenBorrowed;
//}

bool User::operator==(const User& s) const
{
	return *this == s;
}

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


void User::Borrowing(/*id*/)
{
	/*borrowedBooks.push_back(b);
	returningDate(whenBorrowed, 14);
	returningDay = asctime(whenBorrowed);*/

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
	/*InvertedIndex index;
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
	return true;*/
	return false;
}

void User::bookReturn()
{
	ShowBorrowedBooks();
	for (auto elem : borrowedBooks)
	{
		std::cout << "Select?(y/n)";
		char opt;
		std::cin >> opt;

		borrowedBooks.erase(borrowedBooks.begin(),borrowedBooks.begin()+1);
		if (opt == 'y' || opt == 'Y') {

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
			borrowedBooks.erase(borrowedBooks.begin(), borrowedBooks.begin() + 1);
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

void User::LoginMenu()
{
	std::cout << "Please input your username";
	std::string nickname;
	std::cin >> nickname;
	std::cout << "Please input your password";
	std::string pass = "";
	char ch;
	ch = _getch();
	while (ch != 10)
	{
		pass.push_back(ch);
		std::cout << "*";
		ch = _getch();
	}
	if (nickname != this->username || pass != this->password)
	{
		std::cout << "Username and/or password are incorrect";
		LoginRegisterMenu();
	}
	else
	{
		ShowMenu();
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

void User::RegisterMenu()
{
	std::string username, pw, cpw;
	std::cout << "\nUsername: ";
	std::cin >> username;
	std::cout << "Password: ";
	std::cin >> pw;
	std::cout << "Confirm password: ";
	std::cin >> cpw;
	if (pw == cpw)
	{
		if (PasswordRequirements(pw))
		{
			User newUser(username, pw);
			ShowMenu();
		}
		else
		{
			std::cout << "\nPassword doesn't match the requirements, please repeat.";
			RegisterMenu();
		}
	}
	else
	{
		std::cout << "\nPassword and confirm pawword do not match, pelase repeat.";
		RegisterMenu();
	}
}


void User::ShowMenu()
{
	int opt = 1;

	while (opt)
	{
		MenuList();
		std::cin >> opt;
		while (opt < 1 || opt>8)
		{
			std::cout << "\nInvalid option, please try again (1-8).";
			std::cin >> opt;
		}
		std::string keyword;
		switch (opt)
		{
		case 1:
			std::cout << "\nPlease introduce the title/author/ISBN of the book you would like to borrow: ";
			std::cin >> keyword;
			if (search(keyword))
				Borrowing();

			break;
		case 2:
			ShowBorrowedBooks();
			break;
		case 3:
			std::cout << "\nIntroduce the title/author/ISBN of the book you would like to look for: ";
			std::cin >> keyword;
			search(keyword);
			break;
		case 4:
			ReadBook();
			break;
		case 5:
			ChangePassword();
			break;
		case 6:
			LoginRegisterMenu();
			break;
		case 7:
			this->username = '\0';
			this->password = '\0';
			this->borrowedBooks.resize(0);
			std::cout << "\nYour account has been deleted.";
			LoginRegisterMenu();
			break;
		case 8:
			return;
			break;
		default:
			break;
		}

	}
}

void User::ChangePassword()
{
	std::string newPassword, password;
	std::cout << "Input old password: ";
	std::cin >> password;
	if (this->password == password)
	{
		std::cout << "Input new password: ";
		std::cin >> newPassword;
		if (PasswordRequirements(newPassword))
			this->password = newPassword;
		else
		{
			std::cout << "The new password doesn't meet the requirements.\n";
			char opt;
			std::cout << "Do you still want to change your password? (y/n)";
			std::cin >> opt;

			while (opt == 'y' || opt == 'Y' || opt == 'n' || opt == 'N')
			{
				std::cout << "\nInvalid option, please try again. ";
				std::cin >> opt;
			}

			if (opt == 'y' || opt == 'Y')
				ChangePassword();
			else if (opt == 'n' || opt == 'N')
				return;
		}
	}
}

void User::MenuList()
{
	std::cout << "\n---------------------------------------------------------\n";
	std::cout << "Hello " << this->username << "! Please select an option: ";
	std::cout << "\n1. Borrow a book. ";
	std::cout << "\n2. Show borrowed books. ";
	std::cout << "\n3. Search a book. ";
	std::cout << "\n4. Read book. ";
	std::cout << "\n5. Change password. ";
	std::cout << "\n6. Log out. ";
	std::cout << "\n7. Delete account. ";
	std::cout << "\n8. Exit.";
	std::cout << "\n---------------------------------------------------------\n";
}

bool User::PasswordRequirements(std::string pw)
{
	bool UpperLetter = false;
	bool isDigit = false;
	if (pw.size() < 8)
		return false;
	for (int i = 0; i < pw.length(); i++)
	{
		if (isupper(pw[i]))
		{
			UpperLetter = true;
		}
	}
	if (UpperLetter == false)
		return false;

	for (int i = 0; i < pw.length(); i++)
	{
		if (isdigit(pw[i]))
		{
			isDigit = true;
		}
	}
	if (isDigit == false)
		return false;
	return true;
}


