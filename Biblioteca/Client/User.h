#pragma once
#include <string>
#include <vector>
#include "Book.h"

class User {
private:
	std::string username;
	std::vector<Book> borrowedBooks;
public:
	User() = default;
	User(std::string, std::vector<Book>);
	User(const User&);
};