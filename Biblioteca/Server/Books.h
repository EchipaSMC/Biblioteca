#pragma once
#include <iostream>

class Books
{
public:
	Books();
	Books(int id, int bookId, int bestBookId, int workId, int booksCount, int ratingsCount, int workRatingsCount, int workTextReviewsCount, int ratings1,
		int ratings2, int ratings3, int ratings4, int ratings5, std::string isbn, std::string isbn13, std::string authors, std::string originalPublicationYear,
		std::string originalTitle, std::string title, std::string languageCode, std::string imageUrl, std::string smallImageUrl);

private:
	int id, bookId, bestBookId, workId, booksCount, ratingsCount, workRatingsCount, workTextReviewsCount, ratings1, ratings2, ratings3, ratings4, ratings5;
	std::string isbn, isbn13, authors, originalPublicationYear, originalTitle, title, languageCode, imageUrl, smallImageUrl;
	double averageRating;

};
