#include "Invoker.h"

Invoker::Invoker(Document* _doc) {
	doc = _doc;
}

void Invoker::Do(std::string cmdName, std::istream& inpStream) {
	command = nullptr;
	command = cmdCreator::createCommand(inpStream, cmdName);
	if (command != nullptr) {
		command->setDocument(doc);
		command->Execute();
		if (cmdName != "copy") DoneCommands.push_back(command);//
	}
}

void Invoker::Do(cmd inp)
{
	command = nullptr;
	switch (inp.code)
	{
	case 'c':
		command = new CopyCommand(inp.idx1, inp.idx2);
		break;
	case 'p':
		command = new PasteCommand(inp.idx1);
		break;
	case 'i':
		command = new InsertCommand(inp.idx1, inp.str);
		break;
	case 'd':
		command = new DeleteCommand(inp.idx1, inp.idx2);
		break;
	default:
		break;
	}
	if (command != nullptr) {
		command->setDocument(doc);
		command->Execute();
		if (inp.code != 'c') DoneCommands.push_back(command);//
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

void Invoker::Show() {
	doc->Show();
}