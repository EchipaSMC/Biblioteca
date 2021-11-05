#include "Ratings.h"

Ratings::Ratings()
{
	bookId = 0;
	userId = 0;
	rating = 0;
}

Ratings::Ratings(const int& bookId, const int& userId, const int& rating)
{
	this->bookId = bookId;
	this->userId = userId;
	this->rating = rating;
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


