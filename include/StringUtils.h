
#ifndef __STRINGUTILS__H__
#define __STRINGUTILS__H__

#include <string>
#include <vector>

namespace StringUtils {
	// Returns true if the string ends with the given substring
	bool EndsWith(std::string const& str, std::string const& en);

	// Trim space from the beginning of a string
	void LeftTrim(std::string& s);

	// Trim space from the end of a string
	void RightTrim(std::string& s);

	// trim from both ends of a string.  Returns a new string with the trimmed whitespace
	std::string Trim(std::string s);

	// Split a string into a vector of strings, using the given delimiter
	std::vector<std::string> Split(std::string s, std::string delimiter);
}

#endif  //!__STRINGUTILS__H__
