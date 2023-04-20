
#ifndef __STRINGUTILS__H__
#define __STRINGUTILS__H__

#include <string>
#include <vector>

namespace StringUtils {
	// Returns true if the string ends with the given substring
	bool ends_with(std::string const& str, std::string const& en);

	// Trim space from the beginning of a string
	void ltrim(std::string& s);

	// Trim space from the end of a string
	void rtrim(std::string& s);

	// trim from both ends.  Returns a new string with the trimmed whitespace
	std::string trim(std::string s);

	std::vector<std::string> split(std::string s, std::string delimiter);
}

#endif  //!__STRINGUTILS__H__
