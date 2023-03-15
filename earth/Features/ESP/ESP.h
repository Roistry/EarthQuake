#pragma once
class ESP : public FeatureBase
{
public:
	virtual void OnInit() override;
	virtual void OnLoop() override;
	virtual void OnUnInit() override;
	virtual void OnRender() override;
};