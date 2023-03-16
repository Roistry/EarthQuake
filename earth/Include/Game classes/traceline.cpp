#include "pch.h"

typedef int(__cdecl* tCG_Trace)(int* result, int start, int mins, int maxs, int end, int skipNumber, int mask);
tCG_Trace oCG_Trace = (tCG_Trace)(Globals::Game::cgamex86ModuleBase + 0x44040);

extern bool IsVisible(Entity target)
{
	int traceResult[14];
	float start[3];
	start[0] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C838);
	start[1] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C83C);
	start[2] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C840);

	float end[3];
	end[0] = Globals::Game::entityList->aEntities[1].pos.x;
	end[1] = Globals::Game::entityList->aEntities[1].pos.y;
	end[2] = Globals::Game::entityList->aEntities[1].pos.z;

	oCG_Trace(traceResult,
		(int)start,
		0,
		0,
		(int)end,
		0,
		1);

	return !traceResult[12];
}