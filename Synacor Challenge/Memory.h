#pragma once
#define MEMORY_SIZE (2^15)

class Memory
{
public:
	Memory();
	short get_register(short register_number);
	void set_register(short register_number, short value);
private:
	short* m_memory = new short[MEMORY_SIZE];
};

