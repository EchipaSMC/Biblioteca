#pragma once
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct wordPosition {
	int line;
	int index;
};

class InvertedIndex {
	std::map<std::string, std::vector<wordPosition>> Dictionary;
public:
	void addFile(const std::string&);
	std::map<std::string, std::vector<wordPosition>> getDictionary();
	int getLine(std::string&,int);
	int getIndex(std::string&, int);
	//int LevenshteinDistance(const std::string&, const std::string&);

};
