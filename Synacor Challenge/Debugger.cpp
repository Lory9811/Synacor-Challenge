#include "Debugger.h"
#include "System.h"

#include <iostream>

Debugger::Debugger()
{
}


Debugger::~Debugger()
{
}

BOOL Debugger::signalHandler(DWORD signal) {
	if (signal == CTRL_BREAK_EVENT) {
		sys.StartDebug();
		debugConsole();
	}

	return TRUE;
}

void Debugger::debugConsole() {
	std::cin.clear();
	while (sys.get_status() == sys.DEBUGGING) {
		std::cout << "monitor>";
		std::string command;
		std::cin >> command;
		commandProcessor(command);
	}
}

void Debugger::commandProcessor(std::string command) {
	std::vector<std::string> parsedCommand = commandParser(command);

	if (!parsedCommand.empty()) {
		if (parsedCommand[0] == "quit" || parsedCommand[0] == "q")
			sys.StopDebug();
	}
}

std::vector<std::string> Debugger::commandParser(std::string command) {
	std::vector<std::string> parsedCommand = std::vector<std::string>();
	std::string tmp = "";

	for (auto i = command.begin(); i != command.end(); i++) {
		if (*i != ' ' || *i != '\n')
			tmp += *i;
		else
			parsedCommand.push_back(tmp); tmp = "";
	}

	return parsedCommand;
}
