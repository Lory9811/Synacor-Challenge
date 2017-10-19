#pragma once
#include "CPU.h"

#include <string>

static class System
{
public:
	enum Status { IDLE, RUNNING, STOPPED };
	System();
	void Start(std::string binary);
	void Quit();
	void Update();
	Status get_status();
	void DebugMessage(std::string);
private:
	Status status;
	CPU m_cpu;
	Memory memory;
} sys;
