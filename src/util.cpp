#include "stdafx.hpp"

/**
 * @brief Split string to delimiter
 * 
 * @param _string Target string
 * @param _delimiter Delimiter
 * @return vector<string> Vector of string token
 */
vector<string> string_split(const string _string, char _delimiter)
{
    vector<string> tokens;
    size_t start = 0;
    size_t end = 0;
    while ((end = _string.find(_delimiter, start)) != string::npos)
    {
        tokens.push_back(_string.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(_string.substr(start));
    return tokens;
}