#include "Memory.h"
#include "System.h"

#include <memory>


Memory::Memory() {
	memset(m_memory, 0x0000, sizeof(short) * MEMORY_SIZE);
}

void Memory::LoadBinary(std::ifstream* file) {
	char sector[2];
	short address = 0;
	while (!file->eof()) {
		file->read(sector, 2);
		unsigned short value = ((unsigned short)sector[1] << 8) | sector[0];
		m_memory[address] = value;
		address++;
	}
}

short Memory::get_register(short register_number) {
	return m_memory[REGISTERS_ADDRESS + register_number];
}

void Memory::set_register(short register_number, short value) {
	m_memory[REGISTERS_ADDRESS + register_number] = value;
}

short Memory::pop_stack() {
	if (Stack.empty())
		return -1;
	short result = Stack.top();
	Stack.pop();
	return result;
}

void Memory::push_stack(short value) {
	Stack.push(value);
}

short Memory::get_value(short address) {
	return m_memory[address];
}

void Memory::set_value(short address, short value) {
	m_memory[address] = value;
}