#include "BookTags.h"

BookTags::BookTags()
{
	goodReadsBookId = 0;
	tagId = 0;
	count = 0;
}

BookTags::BookTags(std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	result >> word;
	goodReadsBookId = std::stoi(word);

	result >> word;
	tagId= std::stoi(word);

	result >> word;
	count= std::stoi(word);
}

BookTags::BookTags(int goodReadsBookId, int tagId, int count)
{
	this->goodReadsBookId = goodReadsBookId;
	this->tagId = tagId;
	this->count = count;
}

std::string BookTags::GetTags(const int& bestBookId) const
{
	std::string query = "SELECT goodreads_book_id,tag_id,count FROM BookTags INNER JOIN Books o ON goodreads_book_id = o.best_book_id WHERE goodreads_book_id = ";
	query += std::to_string(bestBookId);
}

void BookTags::SetGoodReadsBookId(int goodReadsBookId)
{
	this->goodReadsBookId = goodReadsBookId;
}

void BookTags::SetTagId(int tagId)
{
	this->tagId = tagId;
}

void BookTags::SetCount(int count)
{
	this->count = count;
}

int BookTags::GetGoodReadsBookId() const
{
	return goodReadsBookId;
}

int BookTags::GetTagId() const
{
	return tagId;
}

int BookTags::GetCount() const
{
	return count;
}
