#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include <iostream>

class User {
private:
	std::string username;
	std::vector<Book> borrowedBooks;
public:
	User() = default;
	User(std::string, std::vector<Book>);
	User(const User&);
	std::string GetUsername() const;
	std::vector<Book> GetBorrowedBooks() const;
	void ShowBorrowedBooks(const std::string&, const std::vector<Book>&);
};