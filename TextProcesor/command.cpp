#include "command.h"

void Command::setDocument(std::shared_ptr<Document> _doc) {
	doc = _doc;
	docData = std::make_shared<std::string>(doc->data());
	docBuffer = std::make_shared<std::string>(doc->buffer());
}

void InsertCommand::Execute() {
	//std::string& docData = doc->data();
	if (idx1 <= docData->size())
		docData->insert(idx1, str);
	else
		docData->insert(docData->size(), str);
}

void InsertCommand::unExecute() {
	//std::string& docData = doc->data();
	docData->erase(idx1, str.size());
}

void isCorrectIndex(int& idx1, int& idx2, size_t size) {
	if (idx1 < 0) idx1 = 0;
	if (idx1 > idx2) {
		int c = idx2;
		idx2 = idx1;
		idx1 = c;
	}
	if (idx1 > size) idx1 = size;
	if (idx2 > size) idx2 = size;
}

void DeleteCommand::Execute() {
	//std::string& docData = doc->data();
	isCorrectIndex(idx1, idx2, docData->size());
	delstr = docData->substr(idx1, idx2 - idx1 + 1);
	docData->erase(idx1, idx2 - idx1 + 1);
}

void DeleteCommand::unExecute() {
	//std::string& docData = doc->data();
	docData->insert(idx1, delstr);
}

void CopyCommand::Execute() {
	std::string& docData = doc->data();
	std::string& docBuffer = doc->buffer();
	isCorrectIndex(idx1, idx2, docData.size());
	docBuffer = docData.substr(idx1, idx2 - idx1 + 1);
}

void PasteCommand::Execute() {
	std::string& docData = doc->data();
	std::string& docBuffer = doc->buffer();
	if (idx1 < 0) idx1 = 0;
	if (idx1 > docData.size()) idx1 = docDatasize();
	docData.insert(idx1, docBuffer);
}

void PasteCommand::unExecute() {
	std::string& docData = doc->data();
	std::string& docBuffer = doc->buffer();
	docData.erase(idx1, idx1 + docBuffer.size());
}
