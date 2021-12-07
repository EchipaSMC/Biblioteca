#include "Tags.h"

Tags::Tags(const Tags& tags)
{
	this->tagId = tags.GetTagId();
	this->tagName = tags.GetTagName();
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

	std::getline(result, word, '|');
	this->tagId = std::stoi(word);

	std::getline(result, word, '|');
	this->tagName = std::stoi(word);
}

int Tags::GetTagId()const
{
	return tagId;
}

std::string Tags::GetTagName() const
{
	return tagName;
}

void Tags::SetTagId(const int &tagId)
{
	this->tagId = tagId;
}

void Tags::SetTagName(const std::string &tagName)
{
	this->tagName = tagName;
}

Tags& Tags::operator=(const Tags& tags)
{
	if (this == &tags)
		return *this;
	this->tagId = tagId;
	this->tagName = tagName;
	return *this;
}
