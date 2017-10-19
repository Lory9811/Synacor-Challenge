#pragma once
#include "Memory.h"
#include "opcode.h"
#include "System.h"

#include <array>

class CPU
{
public:
	CPU(Memory memory);
	~CPU();
	void ExecuteOpCode(unsigned char id, short* args);
private:
	Memory memory;
	static void op_halt(CPU, short*);
	static void op_set(CPU, short*);
	static void op_push(CPU, short*);
	static void op_pop(CPU, short*);
	static void op_eq(CPU, short*);
	std::array<opcode, 22> opcodes = {
		opcode {(short)0, &op_halt},
		opcode {(short)1, &op_set}
	};
};

