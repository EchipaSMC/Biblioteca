#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <ctime>
#include <conio.h>
#include "InvertedIndex.h"
#include "Book.h"

class User {
private:
	std::string username;
	std::list<Book> borrowedBooks;
	tm* whenBorrowed;
	std::string returningDay;
	std::string password;

public:
	User();
	~User();
	User(std::string, std::list<Book>, std::string);
	User(std::string,std::string);
	User(const User&);
	std::string GetUsername() const;
	std::list<Book> GetBorrowedBooks() const;
	//tm* GetReturnDate();
	//std::string GetReturnDate();
	//std::string GetPassword();
	void ShowBorrowedBooks();
	void Borrowing(std::string&);
	void returningDate(tm* currentDate, int days);
	void bookReturn();
	bool search(std::string word);
	void ProlongBorrowDate(tm* retDate, int days);
	void BookReturnSpecific(int IdBook);
	void ReadBook();
	void LoginMenu();
	void LoginRegisterMenu();
	void RegisterMenu();
	void ShowMenu();
};