#include "Tags.h"

Tags::Tags()
{
	tagId = -1;
	tagName = "";
}

Tags::Tags(const int& tagId, const std::string& tagName)
{
	this->tagId = tagId;
	this->tagName = tagName;
}

Tags::Tags(std::string queryResult)
{
	std::string word;
	std::stringstream result;
	result << queryResult;

	result >> word;
	tagId = std::stoi(word);

	result >> word;
	tagName = std::stoi(word);
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
