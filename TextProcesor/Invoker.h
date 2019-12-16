#pragma once

#include <vector>
#include "command.h"
#include "document.h"
#include "cmdCreator.h"

class Invoker {
	std::vector<Command*> DoneCommands;
	std::vector<Command*> DeletedCommand;
	std::shared_ptr<Document> doc;
	//Document* doc;
	Command* command;
public:
	Invoker(std::shared_ptr<Document> _doc);
	void Do(const std::string& cmdName, std::istream& inpStream);
	void Undo();
	void Redo();
	void Show(std::ostream& outputStream);
};