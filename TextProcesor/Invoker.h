#pragma once

#include <vector>
#include "command.h"
#include "document.h"
#include "Parser.h"

class Invoker {
	std::vector<Command*> DoneCommands;
	std::vector<Command*> DeletedCommand;
	Document* doc;
	Command* command;
public:
	Invoker(Document* _doc);
	void Do(std::string cmdName, std::istream inpStream);
	void Do(cmd inp);
	void Undo();
	void Redo();
	void Show();
};