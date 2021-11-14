#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include <iostream>
#include <list>
#include <ctime>
#include "InvertedIndex.h"

class User {
private:
	std::string username;
	std::list<Book> borrowedBooks;
	tm* whenBorrowed;
	std::string returningDay;

public:
	User();
	User(std::string, std::list<Book>);
	User(const User&);
	std::string GetUsername() const;
	std::list<Book> GetBorrowedBooks() const;
	//tm* GetReturnDate();
	//std::string GetReturnDate();
	void ShowBorrowedBooks();
	void Borrowing(std::string&);
	void returningDate(tm* currentDate, int days);
	void bookReturn();
	bool search(std::string word);
	void ProlongBorrowDate(tm* retDate, int days);
	void BookReturnSpecific(int IdBook);
};