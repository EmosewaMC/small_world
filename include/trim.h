#ifndef __TRIM__H__
#define __TRIM__H__

#include <cstdint>
#include <string>
#include "Logger.h"

// trim from start
static inline std::string &ltrim(std::string &s) {
    int32_t firstNonWhitespace = -1;
    for (int32_t i = 0; i < s.size(); i++) {
        if (!std::isspace(s.at(i))) break;
        else firstNonWhitespace = i;
    }
    if (firstNonWhitespace != -1) s.erase(s.begin(), s.begin() + firstNonWhitespace);
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    int32_t firstNonWhitespace = -1;
    for (int32_t i = s.length() - 1; i > 0; i--) {
        if (!std::isspace(s.at(i))) break;
        else firstNonWhitespace = i;
    }
    if (firstNonWhitespace != -1) s.erase(s.begin() + firstNonWhitespace, s.end());
    return s;
}

// trim from both ends
static inline std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

#endif  //!__TRIM__H__
