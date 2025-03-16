#include "string_util.h"
#include <sstream>
#include <algorithm>


//Split a string

std::vector<std::string> StringUtils::split(const std::string &str)
{
	return split(str, ' ');
}

std::vector<std::string> StringUtils::split(const std::string &str, const char &delim)
{
	std::vector<std::string> tokens;
	std::istringstream ss(str);
	std::string token;

	while(std::getline(ss, token, delim))
	{
		tokens.push_back(token);
	}
	return tokens;
}


//Trim a string
std::string StringUtils::trim(const std::string &str)
{
	return ltrim(rtrim(str));
}

std::string StringUtils::ltrim(const std::string &str)
{
	size_t start = str.find_first_not_of(" \t\n\r");
	return (start == std::string::npos) ? "" : str.substr(start);
}

std::string StringUtils::rtrim(const std::string &str)
{
	size_t end = str.find_last_not_of(" \t\n\r");
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}



//Convert a string to lower case
std::string StringUtils::toLower(const std::string &str)
{
	std::string lower = str;
	std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
	return lower;
}

std::string StringUtils::toUpper(const std::string &str)
{
	std::string upper =str;
	std::transform(upper.begin(),upper.end(),upper.begin(),::toupper);
	return upper;

}


//replace
std::string StringUtils::replace(const std::string &str ,const std::string& from, const std::string& to)
{
	return replace(str,from.c_str(),to.c_str());
}

std::string StringUtils::replace(const std::string &str ,const char& from, const char& to)
{
	std::string retSring = str;
	for (char &c : retSring)
	{
		if (c == from) 
		{
			c = to;
		}
	}
	return retSring;
}



std::string StringUtils::testFunc(const std::string &str)
{
	return replace(str,'a','i');
	// return replace(str,std::string('a'),std::string('i'));
}