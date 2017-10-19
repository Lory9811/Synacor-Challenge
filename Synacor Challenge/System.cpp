#include "System.h"
#include <iostream>

void System::Start() {
	memory = Memory();
	m_cpu = CPU(memory);
	status = RUNNING;
}

void System::Update() {
	m_cpu.ExecuteOpCode(0, nullptr);
	short* args = new short;
	memset(args, 0x00, 0x02);
	*(args + 1) = 0x01;
	m_cpu.ExecuteOpCode(1, args);
}

void System::DebugMessage(std::string msg) {
	std::cout << "Debug message: " << msg << std::endl;
}
