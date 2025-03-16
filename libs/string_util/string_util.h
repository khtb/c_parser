#pragma once
#include <string>
#include <vector>

namespace StringUtils
{
	std::vector<std::string> split(const std::string &str);
	std::vector<std::string> split(const std::string &str, const char &delim);
	std::string trim(const std::string &str);
	std::string ltrim(const std::string &str);
	std::string rtrim(const std::string &str);
	std::string toLower(const std::string &str);
	std::string toUpper(const std::string &str);
	std::string replace(const std::string &str ,const std::string& from, const std::string& to);
	std::string replace(const std::string &str, const char &from, const char &to);
	std::string remove(const std::string &str, const std::string &toRemove);
	std::string remove(const std::string &str, const char &toRemove);
	std::string testFunc(const std::string &str);
}