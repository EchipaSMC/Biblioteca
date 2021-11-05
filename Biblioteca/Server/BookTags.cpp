#include "BookTags.h"

BookTags::BookTags()
{
	goodReadsBookId = 0;
	tagId = 0;
	count = 0;
}

BookTags::BookTags(int goodReadsBookId, int tagId, int count)
{
	this->goodReadsBookId = goodReadsBookId;
	this->tagId = tagId;
	this->count = count;
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
