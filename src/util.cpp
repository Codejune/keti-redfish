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

/**
 * @brief Make full path from tokens
 * 
 * @param _tokens String token vector
 * @return string Path string
 */
string make_path(vector<string> _tokens)
{
    string path = "/";
    for (unsigned int i = 0; i < _tokens.size(); i++)
        if (_tokens[i] != "")
        {
            if (i == 0)
                path = path + _tokens[i];
            else
                path = path + '/' + _tokens[i];
        }
    return path;
}

/**
 * @brief Sort function of string compare
 * 
 * @param _firt_string First string
 * @param _second_string Second string
 * @return true First string faster
 * @return false Second string faster
 */
bool comp(const string &_firt_string, const string &_second_string)
{
    if (_firt_string.size() == _second_string.size())
        return _firt_string < _second_string;
    return _firt_string.size() < _second_string.size();
}


void timer(boost::asio::deadline_timer* _timer, unsigned int *_remain_expires_time)
{
    if (*_remain_expires_time > 0)
    {
        log(debug) << "Session expires remain: " << *_remain_expires_time;
        --(*_remain_expires_time);
        _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(1));
        _timer->async_wait(boost::bind(timer, _timer, _remain_expires_time));
    }
}