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

std::string BorrowedBooks::BorrowedBooksSearch(const int& userIdSearch) const
{
	std::string query = "SELECT * FROM BorrowedBooks WHERE user_id=";
	query += userIdSearch;
	return query;
}

std::string BorrowedBooks::BorrowedBooksInsert(const int& userId, const int& bookId) const
{
	std::string query = "INSERT INTO BorrowedBooks (user_id,book_id)VALUES ('";
	query += std::to_string(userId) + "'," + "'" + std::to_string(bookId) + "')";
	return query;
}

std::string BorrowedBooks::BorrowedBooksDelete(const int& userId, const int& bookId) const
{
	std::string query = "DELETE FROM BorrowedBooks WHERE user_id = '";
	query += std::to_string(userId) + "' AND book_id = '" + std::to_string(bookId) + "'";
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

int BorrowedBooks::GetUserId() const
{
	return userId;
}

int BorrowedBooks::GetBookId() const
{
	return bookId;
}
