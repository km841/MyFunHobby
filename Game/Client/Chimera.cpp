#include "pch.h"
#include "Chimera.h"
#include "Resources.h"
#include "SpineResource.h"
#include "Transform.h"
#include "Clock.h"

Chimera::Chimera()
	: GameObject(LAYER_TYPE::MONSTER)
	, m_pSkeleton(nullptr)
	, m_pAnimationState(nullptr)
{
}

Chimera::~Chimera()
{
	if (m_pSkeleton)
	{
		delete m_pSkeleton;
		m_pSkeleton = nullptr;
	}

	if (m_pAnimationState)
	{
		delete m_pAnimationState;
		m_pAnimationState = nullptr;
	}
}

void Chimera::Awake()
{
	GameObject::Awake();

	shared_ptr<SpineResource> pSkeletonData = GET_SINGLE(Resources)->LoadSkeletonData("ChimeraSkeleton", "..\\Resources\\Spine\\chimera.atlas", "..\\Resources\\Spine\\chimera.json");
	m_pSkeleton = new spine::Skeleton(pSkeletonData->GetSkeletonData());
	assert(m_pSkeleton);

	const Vec3& vMyPos = GetTransform()->GetLocalPosition();

	m_pSkeleton->setX(vMyPos.x);
	m_pSkeleton->setY(vMyPos.y);
	m_pAnimationState = new spine::AnimationState(pSkeletonData->GetAnimationStateData());
}

void Chimera::Start()
{
	GameObject::Start();
}

void Chimera::Update()
{
	GameObject::Update();
	m_pAnimationState->update(OBJECT_DELTA_TIME);
	m_pAnimationState->apply(*m_pSkeleton);
	m_pSkeleton->updateWorldTransform();
}

void Chimera::LateUpdate()
{
	GameObject::LateUpdate();
}

void Chimera::FinalUpdate()
{
	GameObject::FinalUpdate();
}
