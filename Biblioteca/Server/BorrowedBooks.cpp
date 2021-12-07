#include "BorrowedBooks.h"

BorrowedBooks::BorrowedBooks(const std::string& queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	std::getline(result, word, '|');
	userId = std::stoi(word);

	std::getline(result, word, '|');
	bookId = std::stoi(word);

	std::getline(result, word, '|');
	borrowDate = word;

	std::getline(result, word, '|');
	returnDate =word;
}

BorrowedBooks::BorrowedBooks(const int& userId, const int& bookId, const std::string& returnDate, const std::string& borrowDate)
	:userId(userId), bookId(bookId) , returnDate(returnDate), borrowDate(borrowDate) {}

BorrowedBooks::BorrowedBooks(const BorrowedBooks& borrowedBook)
{
	userId = borrowedBook.userId;
	bookId = borrowedBook.bookId;
	borrowDate = borrowedBook.borrowDate;
	returnDate = borrowedBook.returnDate;
}

const BorrowedBooks& BorrowedBooks::operator=(const BorrowedBooks& borrowedBook)
{
	if (this == &borrowedBook) return *this;
	userId = borrowedBook.userId;
	bookId = borrowedBook.bookId;
	borrowDate = borrowedBook.borrowDate;
	returnDate = borrowedBook.returnDate;
	return *this;
}

void BorrowedBooks::SetUserId(const int& userId)
{
	this->userId = userId;
}

void BorrowedBooks::SetBookId(const int& bookId)
{
	this->bookId = bookId;
}

void BorrowedBooks::SetReturnDate(const std::string& returnDate)
{
	this->returnDate = returnDate;
}

void BorrowedBooks::SetBorrowDate(const std::string& returnDate)
{
	this->borrowDate = borrowDate;
}

int BorrowedBooks::GetUserId() const
{
	return userId;
}

int BorrowedBooks::GetBookId() const
{
	return bookId;
}

std::string BorrowedBooks::GetReturnDate() const
{
	return this->returnDate;
}

std::string BorrowedBooks::GetBorrowDate() const
{
	return this->borrowDate;
}
