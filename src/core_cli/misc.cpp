#include "misc.h"
#include <cstring>
// Contents: Miscellaneous functions for the core_cli library
//
// This file contains the implementation of the miscellaneous functions for the core_cli library. These functions include utilities for string manipulation and command completion.
std::string str_trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}


char* char_trim(char *str)
{
	char* end;
	while (isspace(*str)) str++;
	if (*str == 0)
		return str;
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) end--;
	*(end + 1) = 0;
	return str;
}
