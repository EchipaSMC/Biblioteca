#include "Tags.h"

Tags::Tags()
{
	tagId = -1;
	tagName = nullptr;
}

Tags::Tags(const int& tagId, const int& tagName)
{
	this->tagId = tagId;
	this->tagName = tagName;
}

int Tags::GetTagId()
{
	return tagId;
}

std::string Tags::GetTagName()
{
	return tagName;
}

void Tags::SetTagId(int tagId)
{
	this->tagId = tagId;
}

void Tags::SetTagName(std::string tagName)
{
	this->tagName = tagName;
}
