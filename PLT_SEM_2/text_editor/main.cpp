#include <iostream>
#include <string>
#include "TextEditor.h"


int main()
{	
	std::string command;
	TextEditor te = TextEditor();
	while(te.isOpen())
	{
		std::cout << ">>";
		std::getline(std::cin, command);
		te.execute(command);
		std::cout << te.getText() << std::endl;
	}
}

