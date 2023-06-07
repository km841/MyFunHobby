#include "pch.h"
#include "SpineResource.h"
#include "SpineTextureLoader.h"

SpineResource::SpineResource(const string& szAtlasPath, const string& szBinaryPath)
	: Object(OBJECT_TYPE::SPINE)
	, m_pAtlas(nullptr)
	, m_pSkeletonData(nullptr)
	, m_pAnimationStateData(nullptr)
{
	m_pTextureLoader = new SpineTextureLoader;
	m_pAtlas = new spine::Atlas(szAtlasPath.c_str(), m_pTextureLoader);

	spine::SkeletonBinary binary(m_pAtlas);
	binary.setScale(2.f);

	m_pSkeletonData = binary.readSkeletonDataFile(szBinaryPath.c_str());
	assert(m_pSkeletonData);
}

SpineResource::~SpineResource()
{

}

void SpineResource::Destroy()
{
	SAFE_DELETE(m_pAtlas);
	SAFE_DELETE(m_pAnimationStateData);
	SAFE_DELETE(m_pSkeletonData);
	SAFE_DELETE(m_pTextureLoader);
}

void SpineResource::Init()
{
	m_pAnimationStateData = new spine::AnimationStateData(m_pSkeletonData);
	assert(m_pAnimationStateData);

	m_pAnimationStateData->setDefaultMix(0.1f);
}
