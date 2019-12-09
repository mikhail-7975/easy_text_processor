#pragma once
#include <string>

class Document {
	std::string _data;
	std::string _buffer;
public:
	size_t bufferSize;
	std::string& data() { return _data; }
	std::string& buffer() { return _buffer; }
	void Show();
};