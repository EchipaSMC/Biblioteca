#pragma once
#include <iostream>
#include <string>
#include <sstream>
class BorrowedBooks
{
public:
	BorrowedBooks() = default;
	BorrowedBooks(const std::string queryResult);
	BorrowedBooks(const int& userId, const int& bookId, const std::string& returnDate, const std::string& borrowDate);

	void SetUserId(const int& userId);
	void SetBookId(const int& bookId);
	void SetReturnDate(const std::string& returnDate);
	void SetBorrowDate(const std::string& returnDate);
	int GetUserId()const;
	int GetBookId()const;
	std::string GetReturnDate()const;
	std::string GetBorrowDate()const;
private:
	//returndate , borrowdate ; update contsrt
	std::string returnDate, borrowDate;
	int userId, bookId;
};

