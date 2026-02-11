#pragma once

#include <iostream>
#include <string>
#include <vector>

class JsonParser {
public:
	JsonParser(std::string* data);
	int parse();
private:
	std::string* parserData;
	std::vector<std::string> keyValuePairs;
};