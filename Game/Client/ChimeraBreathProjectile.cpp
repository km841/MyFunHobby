#include "pch.h"
#include "ChimeraBreathProjectile.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "Tile.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "Clock.h"

ChimeraBreathProjectile::ChimeraBreathProjectile()
	: m_bChecked(false)
	, m_bDespawnFlag(false)
	, m_fRotateZAcc(0.f)
{
}

ChimeraBreathProjectile::~ChimeraBreathProjectile()
{
}

void ChimeraBreathProjectile::Awake()
{
	MonsterProjectile::Awake();
}

void ChimeraBreathProjectile::Start()
{
	MonsterProjectile::Start();
}

void ChimeraBreathProjectile::Update()
{
	MonsterProjectile::Update();

	if (m_bDespawnFlag)
	{
		GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		GetRigidBody()->SetRotationZForDynamic(0.f);
		GetRigidBody()->SetAngularDamping(PX_MAX_F32);
		GetRigidBody()->SetLinearDamping(PX_MAX_F32);
		GetAnimator()->Play(L"VenomProjectile_Despawn", false);

		

		Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
		Vec3 vMySize = GetTransform()->GetLocalPosition();
		GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vMyPos, Vec3(100.f, 100.f, 0.f), Vec3::Zero, 3.f);
		m_bDespawnFlag = false;
	}
	GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 2.f));
	if (GetAnimator()->GetActiveAnimation() && GetAnimator()->GetActiveAnimation()->IsFinished())
	{
		m_bChecked = false;
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
	}
}

void ChimeraBreathProjectile::LateUpdate()
{
	MonsterProjectile::LateUpdate();
}

void ChimeraBreathProjectile::FinalUpdate()
{
	MonsterProjectile::FinalUpdate();
}

void ChimeraBreathProjectile::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType() || LAYER_TYPE::FALLING_OBJECT == pGameObject->GetLayerType())
	{
		// Despawn!
		if (!m_bChecked)
		{
			m_bDespawnFlag = true;
			m_bChecked = true;
		}

	}
}

void ChimeraBreathProjectile::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		// Despawn!
		if (!m_bChecked)
		{
			m_bDespawnFlag = true;
			m_bChecked = true;
		}
	}
}

void ChimeraBreathProjectile::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
