#include "..\TCPSocket\TCPSocket.cpp"
#include "User.h"

User::User()
{
	socket.Connect();
}

User::User(const std::string& username, const std::string& password, const std::vector<BorrowedBooks>& borrowedBooks)
{
	socket.Connect();
	this->username = username;
	this->borrowedBooks = borrowedBooks;
	this->password = password;
}

User::User(const std::string& username, const std::string& password)
{
	socket.Connect();
	this->username = username;
	this->password = password;
	this->borrowedBooks.resize(0);
}

User::User(const User& user)
{
	this->username = user.username;
	this->borrowedBooks = user.borrowedBooks;
	this->password = user.password;
}

std::string User::GetUsername() const
{
	return username;
}

std::vector<BorrowedBooks> User::GetBorrowedBooks() const
{
	return borrowedBooks;
}

bool User::operator==(const User& s) const
{
	return *this == s;
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

void User::RegisterMenu()
{
	std::string username, pw, cpw;
	std::cout << "\nUsername: ";
	std::cin >> username;
	std::cout << "\nPlease note: The password must have at least one digit, a mixture of uppercase and lowercase letters and at least one special character. ";
	std::cout << "Password: ";
	std::cin >> pw;
	std::cout << "Confirm password: ";
	std::cin >> cpw;
	if (pw == cpw)
	{
		if (PasswordRequirements(pw))
		{
			User newUser(username, pw);
			//ShowMenu();
		}
		else
		{
			std::cout << "\nPassword does not meet the requirements, please repeat.";
			RegisterMenu();
		}
	}
	else
	{
		std::cout << "\nPassword and confirm password do not match, pelase repeat.";
		RegisterMenu();
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
		//LoginRegisterMenu();
	}
	else
	{
		//ShowMenu();
	}
}

void User::ReturnBook()
{
	//ShowBorrowedBooks();
	for (auto elem : borrowedBooks)
	{
		std::cout << "Select?(y/n)";
		char opt;
		std::cin >> opt;

		borrowedBooks.erase(borrowedBooks.begin(), borrowedBooks.begin() + 1);
		if (opt == 'y' || opt == 'Y') {

			std::cout << "You have returned the book succesfully. The book is now available in library.";
			elem.setReturningDate("\0");
		}
	}
}

void User::Borrowing(/*id*/)
{
	/*borrowedBooks.push_back(b);
	returningDate(whenBorrowed, 14);
	returningDay = asctime(whenBorrowed);*/

}

void User::ReadBook()
{
	//ShowBorrowedBooks();
	std::cout << "Input the id of the book you want to read: ";
	int IdBook;
	std::cin >> IdBook;
	for (auto elem : borrowedBooks)
	{
		if (IdBook == stoi(elem.getBook().getBookId()))
		{
			std::cout << "You are now reading " << elem.getBook().getTitle() << " written by " << elem.getBook().getAuthor() << std::endl;
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
			//BookReturnSpecific(IdBook);
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

void BookDetails()
{
}

bool User::PasswordRequirements(std::string pw)
{
	bool UpperLetter = false;
	bool LowerLetter = false;
	bool isDigit = false;
	bool specialChar = false;
	if (pw.size() < 8)
		return false;
	for (int i = 0; i < pw.length(); i++)
	{
		if (isupper(pw[i]))
		{
			UpperLetter = true;
		}
		if (islower(pw[i]))
		{
			LowerLetter = true;
		}
		if (isdigit(pw[i]))
		{
			isDigit = true;
		}
		if ((pw[i] > 32 && pw[i] < 48) || (pw[i] > 57 && pw[i] < 65) || (pw[i] > 90 && pw[i] < 97) || (pw[i] > 122 && pw[i] < 127))
		{
			specialChar = true;
		}
	}
	if (UpperLetter == false || LowerLetter == false)
		return false;

	if (isDigit == false)
		return false;

	if (specialChar == false)
		return false;
	return true;
}

void User::returningDate(std::string currentDate, int days)
{
	std::stringstream iss(currentDate);
	std::string partOfDate;
	time_t now = time(NULL);
	tm retDate;
	localtime_s(&retDate, &now);

	std::vector<std::string>fullDate;
	while (std::getline(iss, partOfDate, '/')) {
		fullDate.push_back(partOfDate);
	}
	retDate.tm_mday = stoi(fullDate[0]);
	retDate.tm_mon = stoi(fullDate[1]);
	retDate.tm_year = stoi(fullDate[2]);

	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(&retDate) + (days * one_day);

	localtime_s(&retDate, &date_seconds);
}
