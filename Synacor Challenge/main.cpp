#include "System.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	sys.Start("F:\\Visual Studio 2017\\Projects\\Synacor Challenge\\Debug\\challenge.bin");
	while (sys.get_status() != System::Status::STOPPED) {
		sys.Update();
	}
	std::string tmp = "";
	std::cin >> tmp;

	return 0;
}