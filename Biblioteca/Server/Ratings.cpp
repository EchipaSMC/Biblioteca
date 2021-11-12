#include "Ratings.h"

Ratings::Ratings()
{
	bookId = 0;
	userId = 0;
	rating = 0;
}

Ratings::Ratings(std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	result >> word;
	bookId = std::stoi(word);

	result >> word;
	userId = std::stoi(word);

	result >> word;
	rating = std::stoi(word);
}

Ratings::Ratings(const int& bookId, const int& userId, const int& rating)
{
	this->bookId = bookId;
	this->userId = userId;
	this->rating = rating;
}

std::string Ratings::GetRatings(const int& id) const
{
	std::string query = "SELECT book_id,user_id,rating FROM Ratings INNER JOIN Books o ON ON Ratings.book_id =o.id  WHERE Ratings.book_id = ";
	query += std::to_string(id);
}

int Ratings::GetBookId() const
{
	return bookId;
}

int Ratings::GetUserId() const
{
	return userId;
}

int Ratings::GetRating() const
{
	return rating;
}

void Ratings::SetBookId(int bookId)
{
	this->bookId = bookId;
}

void Ratings::SetUserId(int userId)
{
	this->userId = userId;
}

void Ratings::SetRating(int rating)
{
	this->rating = rating;
}


