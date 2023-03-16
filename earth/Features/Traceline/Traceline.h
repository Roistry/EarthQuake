#pragma once

// void
typedef int(__cdecl* tCG_Trace)(trace_t* result, Vector3 start, Vector3 mins, Vector3 maxs, Vector3 end, int skipNumber, int mask);

class Traceline : public FeatureBase
{
public:
	static tCG_Trace oCG_Trace;

	virtual void OnInit() override;
	virtual void OnLoop() override;
	virtual void OnUnInit() override;
	virtual void OnRender() override;
};