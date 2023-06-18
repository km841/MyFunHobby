#include "pch.h"
#include "MagicSword.h"
#include "Clock.h"
#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectRemoveToSceneEvent.h"
#include "MeshRenderer.h"
#include "Material.h"

MagicSword::MagicSword(float fStayTime)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_tStayTime(fStayTime)
	, m_bActive(false)
	, m_tDuration(2.f)
	, m_bDestroyed(false)
{
}

MagicSword::~MagicSword()
{
}

void MagicSword::Awake()
{
	GameObject::Awake();
	m_tStayTime.Start();
}

void MagicSword::Start()
{
	GameObject::Start();
}

void MagicSword::Update()
{
	GameObject::Update();
	m_tStayTime.Update(WORLD_DELTA_TIME);

	if (!m_bActive && m_tStayTime.IsFinished())
	{
		GetAnimator()->Play(L"MagicSword", false);
		m_bActive = true;
	}

	if (GetAnimator()->GetActiveAnimation())
	{
		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			Vec3 vPos = GetTransform()->GetLocalPosition();
			Vec3 vSize = GetTransform()->GetLocalScale();
			GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vPos, vSize, Vec3::Zero, 3.f);
			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}

		if (!m_bDestroyed && GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			m_tDuration.Start();
			m_bDestroyed = true;
		}

		if (m_bDestroyed)
		{
			m_tDuration.Update(WORLD_DELTA_TIME);
			
			GetMeshRenderer()->GetMaterial()->SetFloat(0, std::clamp(1.f - m_tDuration.GetProgress(), 0.01f, 1.f));
			if (m_tDuration.IsFinished())
			{
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
			}
		}
	}

}

void MagicSword::LateUpdate()
{
	GameObject::LateUpdate();
}

void MagicSword::FinalUpdate()
{
	GameObject::FinalUpdate();
}
