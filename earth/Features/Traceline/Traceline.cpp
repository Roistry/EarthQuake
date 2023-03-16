#include "pch.h"
#include "Traceline.h"

tCG_Trace Traceline::oCG_Trace;

void Traceline::OnInit()
{
	Traceline::oCG_Trace = (tCG_Trace)(Globals::Game::cgamex86ModuleBase + 0x44040);
	int traceResult[14];
	float start[3];
	start[0] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C838);
	start[1] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C83C);
	start[2] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C840);

	float end[3];
	end[0] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C838) + *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C844) * 131072.0f;
	end[1] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C83C) + *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C848) * 131072.0f;
	end[2] = *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C840) + *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C84C) * 131072.0f;

	//if doesnt work pass vector3's as ints
	oCG_Trace(traceResult,
		(int)start,
		0,
		0,
		(int)end,
		0,
		MASK_SOLID);

	for (size_t i = 0; i < 14; i++)
		printf("traceResult[%d]: %x\n", i, traceResult[i]);
}

void Traceline::OnLoop()
{

}

void Traceline::OnUnInit()
{

}

void Traceline::OnRender()
{

}