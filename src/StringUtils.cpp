#include "StringUtils.h"

#include "Logger.h"

// Returns true if the string ends with the given substring
bool StringUtils::ends_with(std::string const& str, std::string const& en) {
	if (en.size() > str.size()) return false;
	return std::equal(en.rbegin(), en.rend(), str.rbegin());
}

// Trim space from the beginning of a string
void StringUtils::ltrim(std::string& s) {
	int32_t firstNonWhitespace = -1;
	for (int32_t i = 0; i < s.size(); i++) {
		if (!std::isspace(s.at(i))) break;
		else firstNonWhitespace = i;
	}
	if (firstNonWhitespace != -1) s.erase(s.begin(), s.begin() + firstNonWhitespace + 1);
}

// Trim space from the end of a string
void StringUtils::rtrim(std::string& s) {
	int32_t firstNonWhitespace = -1;
	for (int32_t i = s.length() - 1; i > 0; i--) {
		if (!std::isspace(s.at(i))) break;
		else firstNonWhitespace = i;
	}
	if (firstNonWhitespace != -1) s.erase(s.begin() + firstNonWhitespace, s.end());
}

// trim from both ends
std::string StringUtils::trim(std::string s) {
	rtrim(s);
	ltrim(s);
	return s;
}

std::vector<std::string> StringUtils::split(std::string s, std::string delimiter) {
	int32_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}
