#include "Books.h"

Books::Books(int id, int bookId, int bestBookId, int workId, int booksCount, std::string isbn, std::string isbn13, std::string authors, std::string originalPublicationYear,
	std::string originalTitle, std::string title, std::string languageCode, double averageRating, int ratingsCount, int workRatingsCount, int workTextReviewsCount,
	int ratings1, int ratings2, int ratings3, int ratings4, int ratings5, std::string imageUrl, std::string smallImageUrl) :
	id(id),
	bookId(bookId),
	bestBookId(bestBookId),
	workId(workId),
	booksCount(booksCount),
	isbn(isbn),
	isbn13(isbn13),
	authors(authors),
	originalPublicationYear(originalPublicationYear),
	originalTitle(originalTitle),
	title(title),
	languageCode(languageCode),
	averageRating(averageRating),
	ratingsCount(ratingsCount),
	workRatingsCount(workRatingsCount),
	workTextReviewsCount(workTextReviewsCount),
	ratings1(ratings1),
	ratings2(ratings2),
	ratings3(ratings3),
	ratings4(ratings4),
	ratings5(ratings5),
	imageUrl(imageUrl),
	smallImageUrl(smallImageUrl) {}

Books::Books(std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	std::getline(result, word, '|');
	id = std::stoi(word);

	std::getline(result, word, '|');
	bookId = std::stoi(word);

	std::getline(result, word, '|');
	bestBookId = std::stoi(word);

	std::getline(result, word, '|');
	workId = std::stoi(word);

	std::getline(result, word, '|');
	booksCount = std::stoi(word);

	std::getline(result, word, '|');
	isbn = word;

	std::getline(result, word, '|');
	isbn13 = word;

	std::getline(result, word, '|');
	authors = word;

	std::getline(result, word, '|');
	originalPublicationYear = word;

	std::getline(result, word, '|');
	originalTitle = word;

	std::getline(result, word, '|');
	title = word;

	std::getline(result, word, '|');
	languageCode = word;

	std::getline(result, word, '|');
	averageRating = std::stod(word);

	std::getline(result, word, '|');
	ratingsCount = std::stoi(word);

	std::getline(result, word, '|');
	workRatingsCount = std::stoi(word);

	std::getline(result, word, '|');
	workTextReviewsCount = std::stoi(word);

	std::getline(result, word, '|');
	ratings1 = std::stoi(word);

	std::getline(result, word, '|');
	ratings2 = std::stoi(word);

	std::getline(result, word, '|');
	ratings3 = std::stoi(word);

	std::getline(result, word, '|');
	ratings4 = std::stoi(word);

	std::getline(result, word, '|');
	ratings5 = std::stoi(word);

	std::getline(result, word, '|');
	imageUrl = word;

	std::getline(result, word, '|');
	smallImageUrl = word;
}

Books::Books(const Books& book)
{
	id = book.id;
	bookId = book.bookId;
	bestBookId = book.bestBookId;
	workId = book.workId;
	booksCount = book.booksCount;
	isbn = book.isbn;
	isbn13 = book.isbn13;
	authors = book.authors;
	originalPublicationYear = book.originalPublicationYear;
	originalTitle = book.originalTitle;
	title = book.title;
	languageCode = book.languageCode;
	averageRating = book.averageRating;
	ratingsCount = book.ratingsCount;
	workRatingsCount = book.workRatingsCount;
	workTextReviewsCount = book.workTextReviewsCount;
	ratings1 = book.ratings1;
	ratings2 = book.ratings2;
	ratings3 = book.ratings3;
	ratings4 = book.ratings4;
	ratings5 = book.ratings5;
	imageUrl = book.imageUrl;
	smallImageUrl = book.smallImageUrl;
}

const Books& Books::operator=(const Books& book)
{
	if (this == &book) return *this;
	id = book.id;
	bookId = book.bookId;
	bestBookId = book.bestBookId;
	workId = book.workId;
	booksCount = book.booksCount;
	isbn = book.isbn;
	isbn13 = book.isbn13;
	authors = book.authors;
	originalPublicationYear = book.originalPublicationYear;
	originalTitle = book.originalTitle;
	title = book.title;
	languageCode = book.languageCode;
	averageRating = book.averageRating;
	ratingsCount = book.ratingsCount;
	workRatingsCount = book.workRatingsCount;
	workTextReviewsCount = book.workTextReviewsCount;
	ratings1 = book.ratings1;
	ratings2 = book.ratings2;
	ratings3 = book.ratings3;
	ratings4 = book.ratings4;
	ratings5 = book.ratings5;
	imageUrl = book.imageUrl;
	smallImageUrl = book.smallImageUrl;
	return *this;
}

int Books::GetId() const
{
	return id;
}

int Books::GetBookId() const
{
	return bookId;
}

int Books::GetWorkId() const
{
	return workId;
}

int Books::GetBestBookId() const
{
	return bestBookId;
}

int Books::GetBookCount() const
{
	return booksCount;
}

int Books::GetRatingsCount() const
{
	return ratingsCount;
}

int Books::GetWorkRatingsCount() const
{
	return workRatingsCount;
}

int Books::GetWorkTextReviewsCount() const
{
	return workTextReviewsCount;
}

int Books::GetRatings1() const
{
	return ratings1;
}

int Books::GetRatings2() const
{
	return ratings2;
}

int Books::GetRatings3() const
{
	return ratings3;
}

int Books::GetRatings4() const
{
	return ratings4;
}

int Books::GetRatings5() const
{
	return ratings5;
}

double Books::GetAverageRating() const
{
	return averageRating;
}

std::string Books::GetISBN() const
{
	return isbn;
}

std::string Books::GetISBN13() const
{
	return isbn13;
}

std::string Books::GetLanguageCode() const
{
	return languageCode;
}

std::string Books::GetAuthors() const
{
	return authors;
}

std::string Books::GetImageURL() const
{
	return imageUrl;
}

std::string Books::GetSmallImageURL() const
{
	return smallImageUrl;
}

std::string Books::GetTitle() const
{
	return title;
}

std::string Books::GetOriginalTitle() const
{
	return originalTitle;
}

std::string Books::GetOriginalPublicationYear() const
{
	return originalPublicationYear;
}

void Books::SetId(const int& id)
{
	this->id = id;
}

void Books::SetBookId(const int& bookId)
{
	this->bookId = bookId;
}

void Books::SetWorkId(const int& workId)
{
	this->workId = workId;
}

void Books::SetBestBookId(const int& bestBookId)
{
	this->bestBookId = bestBookId;
}

void Books::SetBookCount(const int& bookCount)
{
	this->booksCount = bookCount;
}

void Books::SetRatingsCount(const int& ratingsCount)
{
	this->ratingsCount = ratingsCount;
}

void Books::SetWorkRatingsCount(const int& workRatingsCount)
{
	this->workRatingsCount = workRatingsCount;
}

void Books::SetWorkTextReviewsCount(const int& workTextReviewsCount)
{
	this->workTextReviewsCount = workTextReviewsCount;
}

void Books::SetRatings1(const int& ratings1)
{
	this->ratings1 = ratings1;
}

void Books::SetRatings2(const int& ratings2)
{
	this->ratings2 = ratings2;
}

void Books::SetRatings3(const int& ratings3)
{
	this->ratings3 = ratings3;
}

void Books::SetRatings4(const int& ratings4)
{
	this->ratings4 = ratings4;
}

void Books::SetRatings5(const int& ratings5)
{
	this->ratings5 = ratings5;
}

void Books::SetAverageRating(const double& averageRating)
{
	this->averageRating = averageRating;
}

void Books::SetISBN(const std::string& ISBN)
{
	this->isbn = ISBN;
}

void Books::SetISBN13(const std::string& ISBN13)
{
	this->isbn13 = ISBN13;
}

void Books::SetLanguageCode(const std::string& languageCode)
{
	this->languageCode = languageCode;
}

void Books::SetAuthors(const std::string& authors)
{
	this->authors = authors;
}

void Books::SetImageURL(const std::string& imageURL)
{
	this->imageUrl = imageURL;
}

void Books::SetSmallImageURL(const std::string& smallImageUrl)
{
	this->smallImageUrl = smallImageUrl;
}

void Books::SetTitle(const std::string& title)
{
	this->title = title;
}

void Books::SetOriginalTitle(const std::string& originalTitle)
{
	this->originalTitle = originalTitle;
}

void Books::SetOriginalPublicationYear(const std::string& originalPublicationYear)
{
	this->originalPublicationYear = originalPublicationYear;
}

