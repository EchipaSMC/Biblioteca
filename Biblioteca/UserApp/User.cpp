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

void User::RegisterMenu(std::string username, std::string password)
{
	socket.SendInt(registerUser);
	socket.Send(username);
	socket.Send(password);
	this->username = username;
	this->password = password;
}

void User::LoginMenu(std::string username, std::string password)
{
	socket.SendInt(loginUser);
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
		borrowedBooks[i]=BorrowedBooks(bookToAdd);
	}
}

void User::DeleteAccount()
{
	socket.SendInt(deleteAccount);
	username = "";
	password = "";
	searchedBooks.clear();
	borrowedBooks.clear();
	currentBookTags.clear();
}

void User::Logout()
{
	socket.SendInt(logout);
	username = "";
	password = "";
	searchedBooks.clear();
	borrowedBooks.clear();
	currentBookTags.clear();
}

void User::ReturnBook(int bookToReturnId)
{
	socket.SendInt(returnBook);
	socket.SendInt(bookToReturnId);
	for (auto& book : borrowedBooks)
	{
		if (stoi(book.getBook().getBookId()) == bookToReturnId)
		{
			borrowedBooks.erase(borrowedBooks.begin() + bookToReturnId, borrowedBooks.begin() + bookToReturnId + 1);
		}
	}
}

void User::Borrowing(int bookToBorrowId)
{
	socket.SendInt(borrowBook);
	std::string date;
	time_t now = time(0);
	tm currentDate;
	localtime_s(&currentDate, &now);
	date = "";
	date += std::to_string(currentDate.tm_year + 1900) + '-' + std::to_string(currentDate.tm_mon) + '-' + std::to_string(currentDate.tm_mday);
	
	socket.SendInt(bookToBorrowId);
	socket.Send(date);
	
	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(&currentDate) + (14 * one_day);

	localtime_s(&currentDate, &date_seconds);
	
	date = "";
	date += std::to_string(currentDate.tm_year + 1900) + '-' + std::to_string(currentDate.tm_mon) + '-' + std::to_string(currentDate.tm_mday);
	socket.Send(date);

}

void User::SearchBooks(const std::string& keyword)
{
	socket.SendInt(searchBook);
	int size;
	std::string book;
	socket.Send(keyword);
	socket.ReceiveInt(size);
	searchedBooks.resize(size);
	for (int i = 0; i < searchedBooks.size(); i++)
	{
		socket.Receive(book);
		searchedBooks[i] = Book(book);
	}
}

void User::ReadBook()
{
	socket.SendInt(readBook);
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
		socket.SendInt(changePassword);
		socket.Send(newPassword);
		this->password = newPassword;
	}
}

void User::BookDetails(const int& bookId)
{
	socket.SendInt(bookDetails);
	int tagNumber;
	std::string tag;
	socket.SendInt(bookId);
	socket.ReceiveInt(tagNumber);
	currentBookTags.resize(tagNumber);
	for (int i = 0; i < tagNumber; i++)
	{
		socket.Receive(tag);
		currentBookTags[i] = tag;
	}
	socket.Receive(tag);
	socket.ReceiveInt(tagNumber);
	socket.ReceiveInt(tagNumber);
	socket.ReceiveInt(tagNumber);
	socket.ReceiveInt(tagNumber);
	socket.ReceiveInt(tagNumber);
	socket.Receive(tag);
}

void User::ProlongBorrowDate(const int& bookId, const std::string& returnDate)
{
	socket.SendInt(prolongBorrowDate);
	std::stringstream iss(returnDate);
	std::string date;
	time_t now = time(0);
	tm retDate;
	localtime_s(&retDate, &now);

	std::getline(iss, date, '-');
	retDate.tm_year = stoi(date) - 1900;
	std::getline(iss, date, '-');
	retDate.tm_mon = stoi(date);
	std::getline(iss, date, '-');
	retDate.tm_mday = stoi(date);

	const time_t one_day = 24 * 60 * 60;
	time_t date_seconds = mktime(&retDate) + (14 * one_day);

	localtime_s(&retDate, &date_seconds);
	date = "";
	date += std::to_string(retDate.tm_year + 1900) + '-' + std::to_string(retDate.tm_mon) + '-' + std::to_string(retDate.tm_mday);

	socket.SendInt(bookId);
	socket.Send(date);
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
