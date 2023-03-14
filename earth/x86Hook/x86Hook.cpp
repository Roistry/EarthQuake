#include "pch.h"
#include "x86Hook.h"

x86Hook::x86Hook(x86Detour* detourobj)
{
	this->detourobj = detourobj;
}

DWORD x86Hook::Init()
{
	size_t length = 20;
	this->gateway = VirtualAlloc(NULL, 20, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD oldprot;
	VirtualProtect(this->gateway, length, PAGE_EXECUTE_READWRITE, &oldprot);

	for (size_t i = 0; i < this->detourobj->len; i++)
	{
		*(BYTE*)((DWORD)this->gateway + i) = this->detourobj->stolenBytes[i];
	}

	*(BYTE*)((DWORD)this->gateway + this->detourobj->len) = 0xE9;

	*(DWORD*)((DWORD)this->gateway + this->detourobj->len + 1) = (this->detourobj->Init() - ((DWORD)(this->gateway) + this->detourobj->len + 5));
	
	VirtualProtect(this->gateway, length, oldprot, &oldprot);

	return (DWORD)this->gateway;
}

void x86Hook::UnInit()
{
	this->detourobj->UnInit();
}

void x86Hook::Debug()
{

}
