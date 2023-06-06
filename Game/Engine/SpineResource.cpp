#include "pch.h"
#include "SpineResource.h"

SpineResource::SpineResource(spine::SkeletonData* pSkeletonData)
	: Object(OBJECT_TYPE::SPINE)
	, m_pSkeletonData(pSkeletonData)
	, m_pAnimationStateData(nullptr)
{
}

SpineResource::~SpineResource()
{
}

void SpineResource::Init()
{
	m_pAnimationStateData = new spine::AnimationStateData(m_pSkeletonData);
	assert(m_pAnimationStateData);

	m_pAnimationStateData->setDefaultMix(0.1f);
}
