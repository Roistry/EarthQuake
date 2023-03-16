#include "pch.h"
#include "Traceline.h"

tCG_Trace Traceline::oCG_Trace;

void Traceline::OnInit()
{
	Traceline::oCG_Trace = (tCG_Trace)(Globals::Game::cgamex86ModuleBase + 0x44040);
	trace_t traceResult;
	//if doesnt work pass vector3's as ints
	oCG_Trace(&traceResult,
		Vector3(*(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C838), *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C83C), *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C840)),
		Vector3(),
		Vector3(),
		Vector3(*(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C838) + *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C844) * 131072.0f,
			*(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C83C) + *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C848) * 131072.0f,
			*(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C840) + *(float*)(Globals::Game::cgamex86ModuleBase + 0xA9C84C) * 131072.0f),
		-1,
		MASK_SOLID);
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