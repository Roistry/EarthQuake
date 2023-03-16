#include "pch.h"
#include "FeatureManager.h"

size_t FeatureManager::FindFeature(const char* identifier)
{
	for (size_t i = 0; i < this->features.size(); i++)
	{
		if (strcmp(this->features[i].first, identifier) == 0)
			return i;
	}
	return -1;
}

void FeatureManager::AddFeature(const char* identifier, FeatureBase* feature)
{
	feature->OnInit();
	this->features.push_back(std::pair<const char*, FeatureBase*>(identifier, feature));
}

void FeatureManager::LoopFeature(const char* identifier)
{
	this->features[this->FindFeature(identifier)].second->OnLoop();
}

void FeatureManager::LoopAll()
{
	for (size_t i = 0; i < this->features.size(); i++)
		this->features[i].second->OnLoop();
}

void FeatureManager::RenderFeature(const char* identifier)
{
	this->features[this->FindFeature(identifier)].second->OnRender();
}

void FeatureManager::RenderAll()
{
	for (size_t i = 0; i < this->features.size(); i++)
		this->features[i].second->OnRender();
}

void FeatureManager::RemoveFeature(const char* identifier)
{
	this->features[this->FindFeature(identifier)].second->OnUnInit();
	this->features.erase(this->features.begin() + this->FindFeature(identifier));
}

void FeatureManager::RemoveAll()
{
	for (size_t i = 0; i < this->features.size(); i++)
		this->features.erase(this->features.begin() + i);
}