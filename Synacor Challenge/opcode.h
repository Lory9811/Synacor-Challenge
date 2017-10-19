#pragma once
#include "CPU.h"

struct opcode
{
	unsigned char id;
	void(*function)(CPU, short*);
};