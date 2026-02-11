#include "JsonParser.h"

// Extremely simple json parser, doesn't support arrays, or strings that could interfere with the parsing.
// e.g. '{', '}', ',', ':' or ' ' in either key or value 

JsonParser::JsonParser(std::string data) {
	this->parserData = data;
}

int JsonParser::parse() {
	int dataLength = (*this).parserData.size();
	std::cout << dataLength << std::endl;

	std::string currentParameter;

	for (char c : this->parserData) {
		if (c == '{') continue;
		if (c == ' ') continue;
		if (c == '\"') continue;

		if (c != ':' && c != '}' && c != ',') currentParameter += c;

		else if (c == ':' || c == '}' || c == ',') {
			this->keyValuePairs.push_back(currentParameter);
			currentParameter.clear();
		}
	}

	this->parsed = true;
	return 0;
}

std::string JsonParser::getValue(std::string key) {
	if (!this->parsed) return "";
	for (int i = 0; i < this->keyValuePairs.size(); i++) {
		if (this->keyValuePairs.at(i) == key && this->keyValuePairs.size() > i + 1) {
			return this->keyValuePairs.at(i + 1);
		}
	}
	return "";
}