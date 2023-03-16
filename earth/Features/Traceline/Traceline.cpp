#include "pch.h"
#include "Traceline.h"

tCG_Trace Traceline::oCG_Trace;

void Traceline::OnInit()
{
	Traceline::oCG_Trace = (tCG_Trace)(Globals::Game::cgamex86ModuleBase + 0x44040);
	trace_t traceResult;
	oCG_Trace(&traceResult, )
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