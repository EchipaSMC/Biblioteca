#include "BorrowedBooks.h"

BorrowedBooks::BorrowedBooks(const std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	result >> word;
	userId = std::stoi(word);

	result >> word;
	bookId = std::stoi(word);
}

BorrowedBooks::BorrowedBooks(const int& userId, const int& bookId, const std::string& returnDate, const std::string& borrowDate)
	:userId(userId), bookId(bookId) , returnDate(returnDate), borrowDate(borrowDate) {}

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
