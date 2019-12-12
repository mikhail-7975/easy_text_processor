#include "Invoker.h"
#include <iostream>

Invoker::Invoker(Document* _doc) {
	doc = _doc;
}

void Invoker::Do(const std::string& cmdName, std::istream& inpStream) {
	command = nullptr;
	command = cmdCreator::createCommand(inpStream, cmdName);
	if (command != nullptr) {
		command->setDocument(doc);
		command->Execute();
		if (cmdName != "copy") DoneCommands.push_back(command);//
	}
}

void Invoker::Undo() {
	if (DoneCommands.size() == 0) return;
	command = DoneCommands.back();
	DoneCommands.pop_back();
	command->unExecute();
	DeletedCommand.push_back(command);
	
}

void Invoker::Redo() {
	if (DeletedCommand.size() == 0) return;
	command = DeletedCommand.back();
	DeletedCommand.pop_back();
	command->Execute();
	DoneCommands.push_back(command);
}

void Invoker::Show(std::ostream& outputStream) {
	outputStream << doc->data() << std::endl;
}