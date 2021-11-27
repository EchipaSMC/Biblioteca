#pragma once
#include <iostream>
#include <string>
#include <sstream>

class BookTags
{
public:
	BookTags();
	BookTags(std::string queryResult);
	BookTags(int goodReadsBookId, int tagId, int count);

	void SetGoodReadsBookId(int goodReadsBookId);
	void SetTagId(int tagId);
	void SetCount(int count);
	int GetGoodReadsBookId() const;
	int GetTagId() const;
	int GetCount() const;
private:
	int goodReadsBookId, tagId, count;
};

