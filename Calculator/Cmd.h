#ifndef CMD_H_
#define CMD_H_

#include <string.h>
#include <ctype.h>
#include <algorithm>


#define CMD_EXIST(m)                                              \
	std::string cmd_str;                                          \
std::transform (m.begin(),m.end(),cmd_str.begin(),tolower);  \
if (cmd_str == "q" or cmd_str == "quit" or cmd_str == "exit")     \
break




#endif /// CMD_H_
