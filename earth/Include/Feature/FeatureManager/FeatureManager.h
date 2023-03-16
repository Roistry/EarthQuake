#pragma once
class FeatureManager
{
private:
	size_t FindFeature(const char* identifier);

public:
	std::vector<std::pair<const char*, FeatureBase*>> features;

	void AddFeature(const char* identifier, FeatureBase* feature);

	void LoopFeature(const char* identifier);
	void LoopAll();

	void RenderFeature(const char* identifier);
	void RenderAll();

	void RemoveFeature(const char* identifier);
	void RemoveAll();
};