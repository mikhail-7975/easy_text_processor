#include "Parser.h"

cmd::cmd(std::string inpStr) {
	std::istringstream inp(inpStr);
	std::string w1, w2, w3, w4;
	inp >> w1;

	if (w1 == "insert") {
		code = 'i';
		inp >> this->str;
		str = str.substr(1, str.size() - 2);
		inp >> w3;
		idx1 = std::stoi(w3);
		idx2 = 0;
	}
	else if (w1 == "delete") {
		code = 'd';
		str = "";
		inp >> w2 >> w3;
		idx1 = std::stoi(w2);
		idx2 = std::stoi(w3);
	}
	else if (w1 == "copy") {
		code = 'c';
		inp >> w2 >> w3;
		idx1 = std::stoi(w2);
		idx2 = std::stoi(w3);
	}
	else if (w1 == "paste") {
		code = 'p'; 
		inp >> w2;
		idx1 = std::stoi(w2);
		idx2 = 0;
	}
	else if (w1 == "undo") {
		code = 'u';
		idx1 = 0;
		idx2 = 0;
	}
	else if (w1 == "redo") {
		code = 'r';
		idx1 = 0;
		idx2 = 0;
	}
	else {
		UnknownCommandException();
	}
}
