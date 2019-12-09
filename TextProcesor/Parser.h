#pragma once
#include <string>
#include <exception>
#include <sstream>

struct cmd {
	cmd(std::string inpStr);
	char code;
	size_t idx1, idx2;
	std::string str;
};

class UnknownCommandException : public std::exception {
public:
	UnknownCommandException() : std::exception("unknown command") {}
};