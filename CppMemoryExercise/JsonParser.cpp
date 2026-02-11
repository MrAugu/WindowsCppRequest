#include "JsonParser.h"

JsonParser::JsonParser(std::string* data) {
	this->parserData = data;
}

int JsonParser::parse() {
	int dataLength = (*this).parserData->size();
	std::cout << dataLength << std::endl;

	std::string currentParameter;

	for (char c : *(this->parserData)) {
		if (c == '{') continue;
		if (c == ' ') continue;
		if (c == ',') continue;
		if (c == '\"') continue;

		if (c != ':' && c != '}') currentParameter += c;

		else if (c == ':' || c == '}') {
			this->keyValuePairs.push_back(currentParameter);
			currentParameter.clear();
		}
	}

	return 0;
}