#pragma once
#include <string>
#include <exception>
#include <sstream>

#include "command.h"

struct cmd {
	cmd(std::string inpStr);
	char code;
	size_t idx1, idx2;
	std::string str;
};

class cmdCreator {
public:
	static Command* createCommand(std::istream inputStream, std::string cmdName); 
};


class UnknownCommandException : public std::exception {
public:
	UnknownCommandException() : std::exception("unknown command") {}
};