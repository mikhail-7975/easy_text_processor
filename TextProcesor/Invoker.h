#pragma once

#include <vector>
#include "command.h"
#include "document.h"
#include "cmdCreator.h"

class Invoker {
	std::vector<Command*> DoneCommands;
	std::vector<Command*> DeletedCommand;
	Document* doc;
	Command* command;
public:
	Invoker(Document* _doc);
	void Do(std::string cmdName, std::istream& inpStream);
	void Undo();
	void Redo();
	void Show();
};