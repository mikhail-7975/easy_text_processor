#include "command.h"



void Command::setDocument(Document* _doc) {
	doc = _doc;
}

void InsertCommand::Execute() {
	std::string& data = doc->data();
	if (idx1 <= data.size())
		data.insert(idx1, str);
	else
		data.insert(data.size(), str);
}

void InsertCommand::unExecute() {
	std::string& data = doc->data();
	data.erase(idx1, str.size());
}

void isCorrectIndex(int* idx1, int* idx2, size_t size) {
	if (*idx1 < 0) idx1 = 0;
	if (*idx1 > *idx2) {
		int c = *idx2;
		*idx2 = *idx1;
		*idx1 = c;
	}
	if (*idx1 > size) *idx1 = size;
	if (*idx2 > size) *idx2 = size;
}

void DeleteCommand::Execute() {
	std::string& data = doc->data();
	isCorrectIndex(&idx1, &idx2, data.size());
	delstr = data.substr(idx1, idx2 - idx1 + 1);
	data.erase(idx1, idx2 - idx1 + 1);
}

void DeleteCommand::unExecute() {
	std::string& data = doc->data();
	data.insert(idx1, delstr);
}

void CopyCommand::Execute() {
	std::string& data = doc->data();
	std::string& buffer = doc->buffer();
	isCorrectIndex(&idx1, &idx2, data.size()); 
	buffer = data.substr(idx1, idx2 - idx1 + 1);
	doc->bufferSize = idx2 - idx1 + 1;
}

void PasteCommand::Execute() {
	std::string& data = doc->data();
	std::string& buffer = doc->buffer();
	if (idx1 < 0) idx1 = 0;
	if (idx1 > data.size()) idx1 = data.size();
	data.insert(idx1, buffer);
}

void PasteCommand::unExecute() {
	std::string& data = doc->data();
	std::string& buffer = doc->buffer();
	data.erase(idx1, idx1 + buffer.size());
}
