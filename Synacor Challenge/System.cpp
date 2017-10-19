#include "System.h"

#include <iostream>
#include <fstream>

System::System() {
	memory = Memory();
	m_cpu = CPU(memory);
	status = IDLE;
}

void System::Start(std::string binary) {
	std::ifstream binaryFile(binary, std::ifstream::binary);
	memory.LoadBinary(&binaryFile);
	binaryFile.close();
	status = RUNNING;
}

void System::Update() {
	m_cpu.Fetch();
}

void System::Quit() {
	status = STOPPED;
}

void System::DebugMessage(std::string msg) {
	std::cout << "Debug message: " << msg << std::endl;
}

System::Status System::get_status() {
	return status;
}
