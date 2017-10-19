#include "CPU.h"
#include "System.h"

#include <iostream>
#include <string>

CPU::CPU() {
}

CPU::CPU(Memory memory)
{
	PC = 0;
	this->memory = memory;
}

CPU::~CPU()
{
}

void CPU::Fetch() {
	sys.DebugMessage(std::to_string(PC) + " " + std::to_string(memory.get_value(PC)) + " " + std::to_string(memory.get_value(PC + 1)) + " " + std::to_string(memory.get_value(PC + 2)) + " " + std::to_string(memory.get_value(PC + 3)) + " " + std::to_string(memory.get_value(PC + 4)));
	while (!memory.get_value(PC)){}
	opcodes[memory.get_value(PC)](this);
}

void CPU::op_halt(CPU*) {
	sys.Quit();
}

void CPU::op_set(CPU* vcpu) {
	short argb = vcpu->memory.get_value(++vcpu->PC);
	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	vcpu->memory.set_register(vcpu->memory.get_value(++vcpu->PC) - REGISTERS_ADDRESS, argb);
	vcpu->PC++;
}

void CPU::op_push(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);
	vcpu->memory.push_stack(arga);
	vcpu->PC++;
}

void CPU::op_pop(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;
	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_value(arga, vcpu->memory.pop_stack());
		return;
	}
	vcpu->memory.set_value(arga, vcpu->memory.pop_stack());
}

void CPU::op_eq(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, (short)(argb == argc));
		return;
	}
	vcpu->memory.set_value(arga, (short)(argb == argc));
}

void CPU::op_gt(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, (short)(argb > argc));
		return;
	}
	vcpu->memory.set_value(arga, (short)(argb > argc));
}


void CPU::op_jmp(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);
	vcpu->PC = arga;
}

void CPU::op_jt(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	
	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);

	if (arga != 0)
		vcpu->PC = argb;
	else
		vcpu->PC++;
}

void CPU::op_jf(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);

	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);

	if (arga == 0)
		vcpu->PC = argb;
	else
		vcpu->PC++;
}

void CPU::op_add(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	short sum = (argb + argc) % 32768;

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, sum);
		return;
	}
	vcpu->memory.set_value(arga, sum);
}

void CPU::op_mult(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	short prod = (argb * argc) % 32768;

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, prod);
		return;
	}
	vcpu->memory.set_value(arga, prod);
}

void CPU::op_mod(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	short mod = argb % argc;

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, mod);
		return;
	}
	vcpu->memory.set_value(arga, mod);
}

void CPU::op_and(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	short and = argb & argc;

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, and);
		return;
	}
	vcpu->memory.set_value(arga, and);
}

void CPU::op_or(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	short argc = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);
	if (argc > REGISTERS_ADDRESS)
		argc = vcpu->memory.get_register(argc - REGISTERS_ADDRESS);

	short or = argb | argc;

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, or);
		return;
	}
	vcpu->memory.set_value(arga, or);
}

void CPU::op_not(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);

	short not = (~argb) & 0x7FFF;

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, not);
		return;
	}
	vcpu->memory.set_value(arga, not);
}

void CPU::op_rmem(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);

	short address = vcpu->memory.get_value(argb);

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, address);
		return;
	}
	vcpu->memory.set_value(arga, address);
}

void CPU::op_wmem(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	short argb = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);
	if (argb > REGISTERS_ADDRESS)
		argb = vcpu->memory.get_register(argb - REGISTERS_ADDRESS);

	vcpu->memory.set_value(arga, argb);
}

void CPU::op_call(CPU* vcpu) {
	vcpu->memory.push_stack(vcpu->PC + 2);
	short arga = vcpu->memory.get_value(++vcpu->PC);
	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);
	vcpu->PC = arga;
}

void CPU::op_ret(CPU* vcpu) {
	short address = vcpu->memory.pop_stack();
	if (address - 1)
		sys.Quit(); return;
	vcpu->PC = address;
}

void CPU::op_out(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	if (arga > REGISTERS_ADDRESS)
		arga = vcpu->memory.get_register(arga - REGISTERS_ADDRESS);
	std::cout << (char)arga;
	vcpu->PC++;
}

void CPU::op_in(CPU* vcpu) {
	short arga = vcpu->memory.get_value(++vcpu->PC);
	vcpu->PC++;

	char input;
	std::cin.get(&input, 1);

	if (arga > REGISTERS_ADDRESS) {
		arga -= REGISTERS_ADDRESS;
		vcpu->memory.set_register(arga, (short)input);
		return;
	}
	vcpu->memory.set_value(arga, (short)input);
}

void CPU::op_noop(CPU* vcpu) {
	vcpu->PC++;
}