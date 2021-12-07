#include "BorrowedBooks.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

BorrowedBooks::BorrowedBooks(const std::string data)
{
	std::string word;
	std::stringstream stream(data);
	std::vector<std::string> vecData;
	char space_char = ' ';
	while (std::getline(stream, word, space_char)) {
		vecData.push_back(word);
	}

	std::string bookData = vecData[0] + vecData[1] + vecData[2] + vecData[3];
	book=Book(bookData);
	dateWhenBorrowed = vecData[4];
	returningDate = vecData[5];	
}

BorrowedBooks::BorrowedBooks(const Book& book, const std::string& borrowDate, const std::string& retDate)
	:book(book), dateWhenBorrowed(borrowDate), returningDate(retDate)
{
}

Book BorrowedBooks::getBook() const
{
	return this->book;
}

std::string BorrowedBooks::getBorrowDate() const
{
	return dateWhenBorrowed;
}

std::string BorrowedBooks::getReturningDate() const
{
	return returningDate;
}

void BorrowedBooks::setBorrowingDate(std::string borrowDate)
{
	this->dateWhenBorrowed = borrowDate;
}

void BorrowedBooks::setReturningDate(std::string retDate)
{
	this->returningDate = retDate;
}
