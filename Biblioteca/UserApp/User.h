#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Book.h"
#include "BorrowedBooks.h"
#include "BookDetails.h"
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
	std::vector<Book> GetSearchedBooks() const;
	std::vector<BorrowedBooks> GetBorrowedBooks() const;
	std::vector<std::string> GetCurrentBookTags() const;
	BookDetails GetBookDetails() const;

	const bool& operator==(const User& s) const;

	void RegisterMenu(std::string username, std::string password);
	void LoginMenu(std::string username, std::string password);
	void DeleteAccount();
	void Logout();
	void ReturnBook(int bookToReturnId);
	void Borrowing(int bookToBorrowId);
	void SearchBooks(const std::string& keyword);
	void ReadBook();
	void ChangePassword(std::string newPassword);
	void CreateBookDetails(const int& bookId);
	void ProlongBorrowDate(const int& bookId, const std::string& returnDate);

	bool PasswordRequirements(std::string pw);

private:
	std::string username;
	std::string password;
	std::vector<Book> searchedBooks;
	std::vector<BorrowedBooks> borrowedBooks;
	std::vector<std::string> currentBookTags;
	BookDetails selectedBook;
	TCPSocket socket;
};