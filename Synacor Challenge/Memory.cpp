#include "Memory.h"
#include "System.h"

#include <memory>


Memory::Memory() {
	memset(m_memory, 0x0000, /*sizeof(unsigned short) */2 * MEMORY_SIZE);
}

void Memory::LoadBinary(std::ifstream* file) {
	char sector[2];
	short address = 0;
	while (!file->eof()) {
		file->read(sector, 2);
		unsigned short hbyte = (unsigned char)sector[1];
		unsigned short value = (hbyte << 8) | (unsigned char)sector[0];
		m_memory[address] = value;
		address++;
	}
}

unsigned short Memory::get_register(unsigned short register_number) {
	return m_memory[REGISTERS_ADDRESS + register_number];
}

void Memory::set_register(unsigned short register_number, unsigned short value) {
	m_memory[REGISTERS_ADDRESS + register_number] = value;
}

unsigned short Memory::pop_stack() {
	if (Stack.empty())
		return -1;
	short result = Stack.top();
	Stack.pop();
	return result;
}

void Memory::push_stack(unsigned short value) {
	Stack.push(value);
}

unsigned short Memory::get_value(unsigned short address) {
	return m_memory[address];
}

void Memory::set_value(unsigned short address, unsigned short value) {
	m_memory[address] = value;
}