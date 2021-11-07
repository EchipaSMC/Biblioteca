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
	void search(std::string word);
	int LevenshteinDistance(const std::string&, const std::string&);

};
