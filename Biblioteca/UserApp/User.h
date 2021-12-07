#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Book.h"
#include "BorrowedBooks.h"
#include <stdlib.h>
#include "..\TCPSocket\TCPSocket.h"

class User {
public:
	User();
	~User()=default;
	User(const std::string& username, const std::string& password, const std::vector<BorrowedBooks>& borrowedBooks);
	User(const std::string& username, const std::string& password);
	User(const User& user);

	std::string GetUsername() const;
	std::vector<BorrowedBooks> GetBorrowedBooks() const;

	bool operator==(const User& s) const;
	
	bool search(std::string word);

	void RegisterMenu();
	void LoginMenu();
	void DeleteAccount();
	void Logout();
	void ReturnBook();
	void Borrowing(/*id*/);
	void SearchBooks();
	void ReadBook();
	void ChangePassword();
	void BookDetails();
	void ProlongBorrowDate(tm* retDate, int days);

	bool PasswordRequirements(std::string pw);
	void returningDate(std::string currentDate, int days);

private:
	std::string username;
	std::string password;
	std::vector<BorrowedBooks> borrowedBooks;
	TCPSocket socket;
};