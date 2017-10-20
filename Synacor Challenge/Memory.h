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
	unsigned short get_register(unsigned short register_number);
	void set_register(unsigned short register_number, unsigned short value);
	unsigned short pop_stack();
	void push_stack(unsigned short value);
	unsigned short get_value(unsigned short address);
	void set_value(unsigned short address, unsigned short value);
private:
	unsigned short* m_memory = new unsigned short[MEMORY_SIZE];
	std::stack<short> Stack;
};

