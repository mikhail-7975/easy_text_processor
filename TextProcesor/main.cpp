#include <iostream>
#include <fstream>

//#include "TextProcessor.h"
#include "command.h"
#include "document.h"
#include "Invoker.h"
#include "parser.h"
#include <exception>

class FReadException : public std::exception {
public:
	FReadException() : std::exception("no file") {}
};

int main() {
	std::fstream inpFile("commands.txt");

	if (!inpFile) {
		std::cout << "no file" << std::endl;
		system("pause");
		return 1;
		//throw FReadException();
	}

	Document doc;

	Invoker inv(&doc);

	//std::string inpstr
	std::string cmdName;
	/*while (std::getline(inpFile, inpstr)) {
		cmd inpCmd(inpstr.c_str());
		switch (inpCmd.code) {
		case 'u':
			inv.Undo();
			break;
		case 'r':
			inv.Redo();
			break;
		default:
			inv.Do(inpCmd);
			break;
		}
		std::cout << "cmd: " << inpCmd.code << " " << inpCmd.str << "; result: ";
		inv.Show(); 
	}*/
	while (inpFile >> cmdName) {
		if (cmdName == "undo") inv.Undo(); 
		else if (cmdName == "redo") inv.Redo();
		else inv.Do(cmdName, inpFile);
	}
	doc.Show();
	system("pause");
}