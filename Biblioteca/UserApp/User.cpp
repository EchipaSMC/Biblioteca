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

const bool& User::operator==(const User& s) const
{
	return (this == &s);
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

void User::RegisterMenu(std::string username, std::string password)
{
	socket.Send(username);
	socket.Send(password);
	this->username = username;
	this->password = password;
}

void User::LoginMenu(std::string username, std::string password)
{
	int borrowedBooksSize;
	socket.Send(username);
	socket.Send(password);
	this->username = username;
	this->password = password;
	socket.ReceiveInt(borrowedBooksSize);
	borrowedBooks.resize(borrowedBooksSize);
	for (int i = 0; i < borrowedBooksSize; i++)
	{
		std::string bookToAdd;
		socket.Receive(bookToAdd);
		borrowedBooks.push_back(BorrowedBooks(bookToAdd));
	}
}

void User::ReturnBook()
{
}

void User::Borrowing(int bookToBorrowId)
{
	std::string date;
	time_t now = time(0);
	tm retDate;
	localtime_s(&retDate, &now);
	date = "";
	date += std::to_string(retDate.tm_year + 1900) + '-' + std::to_string(retDate.tm_mon) + '-' + std::to_string(retDate.tm_mday);
	
	socket.SendInt(bookToBorrowId);
	socket.Send(date);
	
	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(&retDate) + (14 * one_day);

	localtime_s(&retDate, &date_seconds);
	
	date = "";
	date += std::to_string(retDate.tm_year + 1900) + '-' + std::to_string(retDate.tm_mon) + '-' + std::to_string(retDate.tm_mday);
	socket.Send(date);

}

void User::ReadBook()
{
	int IdBook;
	std::string tags;
	std::cin >> IdBook;
	socket.SendInt(IdBook);
	socket.Receive(tags);
}

void User::ChangePassword(std::string newPassword)
{
	if (PasswordRequirements(newPassword))
	{
		socket.Send(newPassword);
		this->password = newPassword;
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
