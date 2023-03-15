#pragma once

class x86Detour
{
public:
	BYTE* source;
	BYTE* destination;
	size_t len;
	BYTE stolenBytes[100];

	x86Detour(BYTE* source, BYTE* destination, size_t len);
	DWORD Init();
	void UnInit();
	void Debug();
};

