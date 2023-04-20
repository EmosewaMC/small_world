#include "StringUtils.h"

#include "Logger.h"

// Returns true if the string ends with the given substring
bool StringUtils::EndsWith(std::string const& str, std::string const& en) {
	if (en.size() > str.size()) return false;
	return std::equal(en.rbegin(), en.rend(), str.rbegin());
}

// Trim space from the beginning of a string
void StringUtils::LeftTrim(std::string& s) {
	int32_t firstNonWhitespace = -1;
	for (int32_t i = 0; i < s.size(); i++) {
		if (!std::isspace(s.at(i))) break;
		else firstNonWhitespace = i;
	}
	if (firstNonWhitespace != -1) s.erase(s.begin(), s.begin() + firstNonWhitespace + 1);
}

// Trim space from the end of a string
void StringUtils::RightTrim(std::string& s) {
	int32_t firstNonWhitespace = -1;
	for (int32_t i = s.length() - 1; i > 0; i--) {
		if (!std::isspace(s.at(i))) break;
		else firstNonWhitespace = i;
	}
	if (firstNonWhitespace != -1) s.erase(s.begin() + firstNonWhitespace, s.end());
}

// trim from both ends
std::string StringUtils::Trim(std::string s) {
	RightTrim(s);
	LeftTrim(s);
	return s;
}

std::vector<std::string> StringUtils::Split(std::string s, std::string delimiter) {
	std::string token;
	std::vector<std::string> result;

	for (auto c : s) {
		if (delimiter.find_first_of(c) != std::string::npos) {
			result.push_back(token);
			token.clear();
		} else {
			token += c;
		}
	}

	result.push_back(token);
	return result;
}
