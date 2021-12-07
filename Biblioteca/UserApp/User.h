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

enum Instructions {
	registerUser = 0,
	loginUser,
	deleteAccount,
	logout,
	returnBook,
	borrowBook,
	searchBook,
	readBook,
	changePassword,
	bookDetails,
	prolongBorrowDate
};

class User {
public:
	User();
	~User()=default;
	User(const std::string& username, const std::string& password, const std::vector<BorrowedBooks>& borrowedBooks);
	User(const std::string& username, const std::string& password);
	User(const User& user);

	std::string GetUsername() const;
	std::vector<BorrowedBooks> GetBorrowedBooks() const;

	const bool& operator==(const User& s) const;
	
	bool search(std::string word);

	void RegisterMenu(std::string username, std::string password);
	void LoginMenu(std::string username, std::string password);
	void DeleteAccount();
	void Logout();
	void ReturnBook(int bookToReturnId);
	void Borrowing(int bookToBorrowId);
	void SearchBooks();
	void ReadBook();
	void ChangePassword(std::string newPassword);
	void BookDetails(const int& bookId);
	void ProlongBorrowDate(const int& bookId, const std::string& returnDate);

	bool PasswordRequirements(std::string pw);
	void returningDate(std::string currentDate, int days);

private:
	std::string username;
	std::string password;
	std::vector<BorrowedBooks> borrowedBooks;
	std::vector<std::string> currentBookTags;
	TCPSocket socket;
};