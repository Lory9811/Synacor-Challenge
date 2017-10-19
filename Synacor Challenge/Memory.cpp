#include "Memory.h"
#include <memory>

#ifndef REGISTERS_ADDRESS
#define REGISTERS_ADDRESS 32768
#endif // !REGISTERS_ADDRESS


Memory::Memory() {
	memset(m_memory, 0x0000, sizeof(short) * MEMORY_SIZE);
}

short Memory::get_register(short register_number) {
	return m_memory[REGISTERS_ADDRESS + register_number];
}

void Memory::set_register(short register_number, short value) {
	m_memory[REGISTERS_ADDRESS + register_number] = value;
}