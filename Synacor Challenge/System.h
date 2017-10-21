#pragma once
#include "CPU.h"

#include <string>

static class System
{
public:
	enum Status { IDLE, RUNNING, STOPPED, DEBUGGING };
	System();
	void Start(std::string binary);
	void StartDebug();
	void Quit();
	void Update();
	void StopDebug();
	Status get_status();
	void DebugMessage(std::string);
private:
	Status status;
	CPU m_cpu;
	Memory memory;
} sys;
