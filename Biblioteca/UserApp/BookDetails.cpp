#include "BookDetails.h"
#include <algorithm>

BookDetails::BookDetails(std::string tags, float averageRating, int ratings1, int ratings2, int ratings3, int ratings4, int ratings5, std::string languageCode, std::string imageUrl) :

	tags(tags),
	averageRating(averageRating),
	ratings1(ratings1),
	ratings2(ratings2),
	ratings3(ratings3),
	ratings4(ratings4),
	ratings5(ratings5),
	languageCode(languageCode),
	imageUrl(imageUrl)
{
	averageRating = std::ceilf(averageRating * 100) / 100;
}

BookDetails::BookDetails(std::string data)
{
	std::stringstream getData(data);
	std::string word;

	std::getline(getData, word, '|');
	tags = word;

	std::getline(getData, word, '|');
	averageRating = std::stof(word);

	std::getline(getData, word, '|');
	ratings1 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings2 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings3 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings4 = std::stoi(word);

	std::getline(getData, word, '|');
	ratings5 = std::stoi(word);

	std::getline(getData, word, '|');
	languageCode = word;

	std::getline(getData, word, '|');
	imageUrl = word;
}

const BookDetails& BookDetails::operator=(const BookDetails& bookDetails)
{
	if (this == &bookDetails) return *this;
	this->tags = bookDetails.tags;
	this->averageRating = bookDetails.averageRating;
	this->ratings1 = bookDetails.ratings1;
	this->ratings2 = bookDetails.ratings2;
	this->ratings3 = bookDetails.ratings3;
	this->ratings4 = bookDetails.ratings4;
	this->ratings5 = bookDetails.ratings5;
	this->languageCode = bookDetails.languageCode;
	this->imageUrl = bookDetails.imageUrl;
	return *this;
}

std::string BookDetails::GetTags() const
{
	return tags;
}

float BookDetails::GetAverageRating() const
{
	return averageRating;
}

int BookDetails::GetRatings1() const
{
	return ratings1;
}

int BookDetails::GetRatings2() const
{
	return ratings2;
}

int BookDetails::GetRatings3() const
{
	return ratings3;
}

int BookDetails::GetRatings4() const
{
	return ratings4;
}

int BookDetails::GetRatings5() const
{
	return ratings5;
}

std::string BookDetails::GetLanguageCode() const
{
	return languageCode;
}

std::string BookDetails::GetImageUrl() const
{
	return imageUrl;
}

void BookDetails::SetTags(const std::string& tags)
{
	this->tags = tags;
}

void BookDetails::SetAverageRating(const float& averageRating)
{
	this->averageRating = averageRating;
}

void BookDetails::SetRatings1(const int& ratings1)
{
	this->ratings1 = ratings1;
}

void BookDetails::SetRatings2(const int& ratings2)
{
	this->ratings2 = ratings2;
}

void BookDetails::SetRatings3(const int& ratings3)
{
	this->ratings3 = ratings3;
}

void BookDetails::SetRatings4(const int& ratings4)
{
	this->ratings4 = ratings4;
}

void BookDetails::SetRatings5(const int& ratings5)
{
	this->ratings5 = ratings5;
}

void BookDetails::SetLanguageCode(const std::string& languageCode)
{
	this->languageCode = languageCode;
}

void BookDetails::SetImageUrl(const std::string imageUrl)
{
	this->imageUrl = imageUrl;
}
