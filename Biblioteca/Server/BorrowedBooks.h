#pragma once
#include <iostream>
#include <string>
#include <sstream>
class BorrowedBooks
{
public:
	BorrowedBooks() = default;
	BorrowedBooks(const std::string queryResult);
	BorrowedBooks(const int& userId, const int& bookId);

	void SetUserId(const int& userId);
	void SetBookId(const int& bookId);
	int GetUserId()const;
	int GetBookId()const;
private:
	int userId, bookId;
};

