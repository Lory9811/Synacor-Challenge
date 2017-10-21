#pragma once
#include <Windows.h>
#include <string>
#include <vector>

static class Debugger
{
public:
	Debugger();
	~Debugger();
	static BOOL WINAPI signalHandler(DWORD signal);
private:
	static void debugConsole();
	static void commandProcessor(std::string);
	static std::vector<std::string> commandParser(std::string);
} debugger ;

