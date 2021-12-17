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
	registerUser = 1,
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
	~User() = default;
	User(const std::string& username, const std::string& password, const std::vector<BorrowedBooks>& borrowedBooks);
	User(const std::string& username, const std::string& password);
	User(const User& user);

	std::string GetUsername() const;
	std::string GetPassword() const;
	void SetUsername(const std::string& username);
	void SetPassword(const std::string& password);
	std::vector<Book> GetSearchedBooks() const;
	std::vector<BorrowedBooks> GetBorrowedBooks() const;
	std::vector<std::string> GetCurrentBookTags() const;
	BookDetails GetBookDetails() const;
	int GetOption() const;
	void SetOption(const int& option);
	int GetBookId()const;
	void SetBookId(const int & bookId);
	std::string GetKeyword()const;
	void SetKeyword(const std::string& keyword);
	bool GetServerError()const;
	bool GetLoginStatus()const;

	inline void StartSubroutine() { clientThread = std::thread(ClientHandler); DetachThread(); };
	inline void DetachThread() { clientThread.detach(); };

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
	bool CheckMaxProlongedDate(const BorrowedBooks& borrowedBooks);
	bool CheckOverdueBooks();

private:
	bool isLoggedIn,serverError;
	std::string username;
	std::string password;
	std::vector<Book> searchedBooks;
	std::vector<BorrowedBooks> borrowedBooks;
	std::vector<std::string> currentBookTags;
	BookDetails selectedBook;
	TCPSocket client = TCPSocket(true);

	std::thread clientThread;
	static int option;

	static void ClientHandler();
	bool ProcessData();

	int bookId;
	std::string keyword;
};
extern User user;