#include "System.h"
#include "Debugger.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	sys.Start(argv[1]);
	SetConsoleCtrlHandler(&debugger.signalHandler, TRUE);
	while (sys.get_status() != System::Status::STOPPED) {
		sys.Update();
	}
	std::string tmp = "";
	std::cin >> tmp;

	return 0;
}