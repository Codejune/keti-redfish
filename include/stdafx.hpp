#ifndef _STDAFX_HPP_
#define _STDAFX_HPP_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <unistd.h>
#include <dirent.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace utility;

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

using namespace logging::trivial;

vector<string> string_split(const string _string, char _delimiter);
string make_path(vector<string> tokens);
#endif