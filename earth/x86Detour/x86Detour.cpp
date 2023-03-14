#include "pch.h"
#include "x86Detour.h"

x86Detour::x86Detour(BYTE* source, BYTE* destination, size_t len)
{
	this->source = source;
	this->destination = destination;
	this->len = len;

	DWORD oldprot;
	VirtualProtect((void*)this->source, this->len, PAGE_EXECUTE_READWRITE, &oldprot);
	memcpy(this->stolenBytes, (void*)this->source, this->len);
	VirtualProtect((void*)this->source, this->len, oldprot, &oldprot);
}

DWORD x86Detour::Init()
{
	DWORD oldprot;
	VirtualProtect((void*)this->source, this->len, PAGE_EXECUTE_READWRITE, &oldprot);

	memset((void*)source, 0x90, this->len);

	*this->source = 0xE9;
	
	DWORD relativeJumpAddress = ((DWORD)this->destination - (DWORD)this->source) - 5;

	*(DWORD*)(this->source + 1) = relativeJumpAddress;

	VirtualProtect((void*)this->source, this->len, oldprot, &oldprot);

	return ((DWORD)this->source + 5);
}

void x86Detour::UnInit()
{
	DWORD oldprot;
	VirtualProtect((void*)this->source, this->len, PAGE_EXECUTE_READWRITE, &oldprot);

	for (size_t i = 0; i < this->len; i++)
	{
		*(this->source + i) = this->stolenBytes[i];
	}

	VirtualProtect((void*)this->source, this->len, oldprot, &oldprot);
}

void x86Detour::Debug()
{
	printf("source: %08x\ndestination: %08x\nlength: %d\n", (DWORD)this->source, (DWORD)this->destination, this->len);
}