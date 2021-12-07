#include "Ratings.h"

Ratings::Ratings(const Ratings& ratings)
{
	this->bookId = ratings.GetBookId();
	this->userId = ratings.GetUserId();
	this->rating = ratings.GetRating();
}

Ratings::Ratings(std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	std::getline(result, word, '|');
	this->bookId = std::stoi(word);

	std::getline(result, word, '|');
	this->userId = std::stoi(word);

	std::getline(result, word, '|');
	this->rating = std::stoi(word);
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

void Ratings::SetBookId(const int &bookId)
{
	this->bookId = bookId;
}

void Ratings::SetUserId(const int &userId)
{
	this->userId = userId;
}

void Ratings::SetRating(const int &rating)
{
	this->rating = rating;
}

Ratings& Ratings::operator=(const Ratings& ratings)
{
	if (this == &ratings)
		return *this;
	this->bookId = ratings.GetBookId();
	this->userId = ratings.GetUserId();
	this->rating = ratings.GetRating();
	return *this;
}


