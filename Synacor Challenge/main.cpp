#include "System.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
	sys.Start("C:\\Users\\Lorenzo.DESKTOP-AO2G7U2\\source\\repos\\Synacor-Challenge\\Synacor Challenge\\Resources\\challenge.bin");
	while (sys.get_status() != System::Status::STOPPED) {
		sys.Update();
	}
	std::string tmp = "";
	std::cin >> tmp;

	return 0;
}