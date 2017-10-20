#pragma once
#include "Memory.h"

#include <array>

class CPU
{
public:
	CPU();
	CPU(Memory memory);
	~CPU();
	void Fetch();
private:
	Memory memory;
	unsigned short PC;

	// Static methods are needed because C++ doesn't like pointers to member functions
	static void op_halt(CPU*);
	static void op_set(CPU*);
	static void op_push(CPU*);
	static void op_pop(CPU*);
	static void op_eq(CPU*);
	static void op_gt(CPU*);
	static void op_jmp(CPU*);
	static void op_jt(CPU*);
	static void op_jf(CPU*);
	static void op_add(CPU*);
	static void op_mult(CPU*);
	static void op_mod(CPU*);
	static void op_and(CPU*);
	static void op_or(CPU*);
	static void op_not(CPU*);
	static void op_rmem(CPU*);
	static void op_wmem(CPU*);
	static void op_call(CPU*);
	static void op_ret(CPU*);
	static void op_out(CPU*);
	static void op_in(CPU*);
	static void op_noop(CPU*);
	std::array<void(*)(CPU*), 22> opcodes = {
		&op_halt,
		&op_set,
		&op_push,
		&op_pop,
		&op_eq,
		&op_gt,
		&op_jmp,
		&op_jt,
		&op_jf,
		&op_add,
		&op_mult,
		&op_mod,
		&op_and,
		&op_or,
		&op_not,
		&op_rmem,
		&op_wmem,
		&op_call,
		&op_ret,
		&op_out,
		&op_in,
		&op_noop
	};
};

