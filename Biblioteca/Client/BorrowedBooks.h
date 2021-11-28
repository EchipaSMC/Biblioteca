#pragma once
#include "Book.h"

class BorrowedBooks {
private:
	Book book;
	std::string dateWhenBorrowed;
	std::string returningDate;
public:
	BorrowedBooks()=default;
	BorrowedBooks(const std::string data);
	BorrowedBooks(const Book& book, const std::string& borrowDate, const std::string& retDate);

	Book getBook()const;
	std::string getBorrowDate() const;
	std::string getReturningDate() const;
	void setBorrowingDate(const std::string&);
	void setReturningDate(const std::string&);
};