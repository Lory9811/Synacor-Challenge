#pragma once
#include "CPU.h"
#include <string>

class System
{
public:
	enum Status { IDLE, RUNNING, STOPPED };
	static void Start();
	static void Quit();
	static void Update();
	static Status get_status();
	static void DebugMessage(std::string);
private:
	static Status status;
	static CPU m_cpu;
	static Memory memory;
};

