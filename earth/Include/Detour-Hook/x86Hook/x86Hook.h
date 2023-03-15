#pragma once

class x86Hook
{
private:
	x86Detour* detourobj;
	void* gateway;
public:
	x86Hook(x86Detour* detourobj);
	DWORD Init();
	void UnInit();
	void Debug();
};