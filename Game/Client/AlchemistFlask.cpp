#include "pch.h"
#include "AlchemistFlask.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "Tile.h"

POOL_INIT(AlchemistFlask);
AlchemistFlask::AlchemistFlask()
	: m_bDespawnFlag(false)
	, m_bChecked(false)
{
}

AlchemistFlask::~AlchemistFlask()
{
}

void AlchemistFlask::Awake()
{
	MonsterProjectile::Awake();
}

void AlchemistFlask::Start()
{
	MonsterProjectile::Start();
}

void AlchemistFlask::Update()
{
	MonsterProjectile::Update();

	if (m_bDespawnFlag)
	{
		GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		GetRigidBody()->SetRotationZForDynamic(0.f);
		GetRigidBody()->SetAngularDamping(PX_MAX_F32);
		GetRigidBody()->SetLinearDamping(PX_MAX_F32);
		GetAnimator()->Play(L"Flask_Despawn", false);
		m_bDespawnFlag = false;
	}

	if (GetAnimator()->GetActiveAnimation() && GetAnimator()->GetActiveAnimation()->IsFinished())
	{
		m_bChecked = false;
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
	}

}

void AlchemistFlask::LateUpdate()
{
	MonsterProjectile::LateUpdate();
}

void AlchemistFlask::FinalUpdate()
{
	MonsterProjectile::FinalUpdate();
}

void AlchemistFlask::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		// Despawn!
		if (!m_bChecked)
		{
			m_bDespawnFlag = true;
			m_bChecked = true;
		}
		
	}
}

void AlchemistFlask::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		// Despawn!
		if (!m_bChecked)
		{
			m_bDespawnFlag = true;
			m_bChecked = true;
		}
		// Player Take Damage!

	}
}

void AlchemistFlask::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
