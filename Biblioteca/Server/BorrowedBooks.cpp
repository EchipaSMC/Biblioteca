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

BorrowedBooks::BorrowedBooks(const int& userId, const int& bookId)
	:userId(userId), bookId(bookId) {}

void BorrowedBooks::SetUserId(const int& userId)
{
	this->userId = userId;
}

void BorrowedBooks::SetBookId(const int& bookId)
{
	this->bookId = bookId;
}

int BorrowedBooks::GetUserId() const
{
	return userId;
}

int BorrowedBooks::GetBookId() const
{
	return bookId;
}
