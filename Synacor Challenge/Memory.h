#pragma once

#ifndef MEMORY_SIZE
#define MEMORY_SIZE 32775
#endif // !MEMORY_SIZE

#ifndef REGISTERS_ADDRESS
#define REGISTERS_ADDRESS 32768
#endif // !REGISTERS_ADDRESS

#include <fstream>
#include <stack>
#include <deque>

class Memory
{
public:
	Memory();
	void LoadBinary(std::ifstream*);
	short get_register(short register_number);
	void set_register(short register_number, short value);
	short pop_stack();
	void push_stack(short value);
	short get_value(short address);
	void set_value(short address, short value);
private:
	unsigned short* m_memory = new unsigned short[MEMORY_SIZE];
	std::stack<short> Stack;
};

