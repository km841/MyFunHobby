#include "pch.h"
#include "ErodedHeavyInfantry.h"
#include "RigidBody.h"
#include "MonsterHPHUD.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Particle.h"
#include "Scene.h"
#include "Scenes.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "LocalEffect.h"
#include "Animator.h"
#include "Animation.h"

POOL_INIT(ErodedHeavyInfantry);
ErodedHeavyInfantry::ErodedHeavyInfantry()
	: m_iAttackCount(0)
	, m_bDeadFlag(false)
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

void ErodedHeavyInfantry::ActivateDeadEvent()
{
	CreateExclamationEffectAndAddedToScene();
	m_bDeadFlag = true;
}

void ErodedHeavyInfantry::CreateExclamationEffectAndAddedToScene()
{
	shared_ptr<LocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<LocalEffect>(L"Forward");
	pLocalEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ExclamationEffect", L"..\\Resources\\Animation\\MonsterCommon\\sign_exclamation_mark.anim");
	pLocalEffect->GetAnimator()->AddAnimation(L"ExclamationEffect", pAnimation);
	pLocalEffect->GetAnimator()->Play(L"ExclamationEffect", true, -1);

	pLocalEffect->GetTransform()->SetParent(GetTransform());

	uint8 iDirection = static_cast<uint8>(GetDirection());
	pLocalEffect->GetTransform()->SetLocalPosition(Vec3(iDirection ? 15.f : -15.f, 160.f, -1.f));

	pLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));

	m_pExclamation = pLocalEffect;
}
