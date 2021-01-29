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
    string sub_string;
    size_t start = 0;
    size_t end = 0;
    while ((end = _string.find(_delimiter, start)) != string::npos)
    {
        sub_string = _string.substr(start, end - start);
        if (sub_string != "" || sub_string != "\0")
            tokens.push_back(sub_string);
        start = end + 1;
    }
    if (_string.substr(start) != "")
        tokens.push_back(_string.substr(start));

    return tokens;
}

string make_path(vector<string> tokens)
{
    string path = "/";
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i] != "") {
            if (i == 0)
                path = path + tokens[i];
            else
                path = path + '/' + tokens[i];
        }
    }
    return path;
}