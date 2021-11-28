#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <ctime>
#include <conio.h>
#include "InvertedIndex.h"
#include "Book.h"
#include "..\TCPSocket\TCPSocket.cpp"

class User {
private:
	std::string username;
	std::vector<Book> borrowedBooks;
	tm* whenBorrowed;
	std::string returningDay;
	std::string password;
	TCPSocket socket;

public:
	User();
	~User();
	User(std::string, std::vector<Book>, std::string);
	User(std::string,std::string);
	User(const std::string&);
	User(const User&);
	std::string GetUsername() const;
	std::vector<Book> GetBorrowedBooks() const;
	//tm* GetReturnDate();
	//std::string GetReturnDate();
	bool operator==(const User& s) const;
	//std::string GetPassword();
	void ShowBorrowedBooks();
	void Borrowing(/*id*/);
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
	void ChangePassword();
	void MenuList();
	bool PasswordRequirements(std::string pw);
};