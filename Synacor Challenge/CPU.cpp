#include "CPU.h"



CPU::CPU(Memory memory)
{
	this->memory = memory;
}

CPU::~CPU()
{
}

void CPU::ExecuteOpCode(unsigned char id, short* args) {
	opcodes[id].function(args);
}

void CPU::op_halt(CPU vcpu, short*) {
	System::DebugMessage("Executing op_halt");
	System::Quit();
}

void CPU::op_set(CPU vcpu, short* args) {
	System::DebugMessage("Executing op_set");
	vcpu.memory.set_register(args[0], vcpu.memory.get_register(args[1]));
}