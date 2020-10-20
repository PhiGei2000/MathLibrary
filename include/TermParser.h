#pragma once
#include "../include/Term.h"

#include <string>
#include <vector>

class TermParser {
private:
	static Term* parseSum(const std::string& sum);
	static Term* parseProduct(const std::string& prod);
	static Term* parseExponentiation(const std::string& exp);
	static Term* parseBrackets(const std::string& str);
	static Term* parseValue(const std::string& str);

public:
	static Term* parse(const std::string& str);
};

