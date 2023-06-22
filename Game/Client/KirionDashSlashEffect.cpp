#include "pch.h"
#include "KirionDashSlashEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"
#include "Clock.h"
#include "CollisionManager.h"
#include "Transform.h"

POOL_INIT(KirionDashSlashEffect);
KirionDashSlashEffect::KirionDashSlashEffect()
	: GameObject(LAYER_TYPE::LOCAL_EFFECT)
	, m_tStayTime(0.5f)
	, m_bStarted(false)
{
	
}

KirionDashSlashEffect::~KirionDashSlashEffect()
{
}

void KirionDashSlashEffect::Awake()
{
	GameObject::Awake();
}

void KirionDashSlashEffect::Start()
{
	GameObject::Start();
}

void KirionDashSlashEffect::Update()
{
	GameObject::Update();

	if (m_tStayTime.IsRunning())
	{
		m_tStayTime.Update(OBJECT_DELTA_TIME);
	}
	else
	{
		m_tStayTime.Start();
	}

	if (m_tStayTime.IsFinished())
	{
		if (GetAnimator())
		{
			if (!m_bStarted)
			{
				GetAnimator()->Play(L"Kirion_Slash_Dash", false);
				m_bStarted = true;
			}
			else
			{
				if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
				{
					// 특정 그룹에게 특정 힘을 준다
					GET_SINGLE(CollisionManager)->SetForceInLayerAndFollowPlayer(
						LAYER_TYPE::PARTICLE, 
						GetTransform()->GetLocalPosition(), 
						GetTransform()->GetLocalScale(), 
						Vec3(0.f, 100.f, 0.f));

					GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
						GetTransform()->GetLocalPosition(),
						GetTransform()->GetLocalScale(),
						Vec3(0.f, 0.f, 0.f),
						static_cast<float>(RANDOM(3, 6)),
						DAMAGE_TYPE::FROM_PLAYER_MAGIC
					);
					

					GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
				}
			}

			if (GetAnimator()->GetActiveAnimation()->IsFinished())
			{
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
				m_tStayTime.Reset();
				m_bStarted = false;
			}
		}
	}
}

void KirionDashSlashEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void KirionDashSlashEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}
