#include "pch.h"
#include "ErodedHeavyInfantry.h"
#include "RigidBody.h"
#include "MonsterHPHUD.h"
#include "Transform.h"

POOL_INIT(ErodedHeavyInfantry);
ErodedHeavyInfantry::ErodedHeavyInfantry()
{
}

ErodedHeavyInfantry::~ErodedHeavyInfantry()
{
}

void ErodedHeavyInfantry::Awake()
{
	Monster::Awake();
	m_Status.ErodedHeavyInfantryMonsterDefaultSetting();
	SetMonsterHPBarWidthAndUnder(80.f, -130.f);
	// HP Bar Size º¯°æ
}

void ErodedHeavyInfantry::Start()
{
	Monster::Start();
}

void ErodedHeavyInfantry::Update()
{
	Monster::Update();
}

void ErodedHeavyInfantry::LateUpdate()
{
	Monster::LateUpdate();
}

void ErodedHeavyInfantry::FinalUpdate()
{
	Monster::FinalUpdate();
}

void ErodedHeavyInfantry::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
		//GetPhysical()->GetActor<PxRigidDynamic>()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
		//GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.f, 0.f, 0.f));
		//GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, 0.f));
	}

	if (LAYER_TYPE::PLAYER_PROJECTILE == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void ErodedHeavyInfantry::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	}

	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void ErodedHeavyInfantry::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void ErodedHeavyInfantry::ScatterParticles(const Vec3& vDir)
{
}

void ErodedHeavyInfantry::ActivateDeadEvent(const Vec3& vDir)
{
}
