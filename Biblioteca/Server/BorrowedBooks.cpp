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
:userId(userId),bookId(bookId){}

std::string BorrowedBooks::BorrowedBooksSearch(const int& userIdSearch) const
{
	std::string query = "SELECT * FROM BorrowedBooks WHERE user_id=";
	query += userIdSearch;
	return query;
}

void BorrowedBooks::SetUserId(const int& userId)
{
	this->userId = userId;
}

void BorrowedBooks::SetBookId(const int& bookId)
{
	this->bookId = bookId;
}

int BorrowedBooks::SetUserId() const
{
	return userId;
}

int BorrowedBooks::SetBookId() const
{
	return bookId;
}
