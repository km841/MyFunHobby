#include "pch.h"
#include "ErodedKnight.h"
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
#include "ObjectReturnToPoolEvent.h"
#include "ObjectRemoveToSceneEvent.h"
#include "MonsterHPHUD.h"

POOL_INIT(ErodedKnight);
ErodedKnight::ErodedKnight()
	: m_bDeadFlag(false)
{
}

ErodedKnight::~ErodedKnight()
{
}

void ErodedKnight::Awake()
{
	Monster::Awake();
	m_Status.ErodedKnightMonsterDefaultSetting();
}

void ErodedKnight::Start()
{
	Monster::Start();
}

void ErodedKnight::Update()
{
	Monster::Update();
}

void ErodedKnight::LateUpdate()
{
	Monster::LateUpdate();
}

void ErodedKnight::FinalUpdate()
{
	Monster::FinalUpdate();
}

void ErodedKnight::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
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

void ErodedKnight::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
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

void ErodedKnight::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void ErodedKnight::ScatterParticles(const Vec3& vDir)
{
	for (int32 i = 0; i < m_vTextureNames.size(); ++i)
	{
		shared_ptr<Particle> pParticle = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<Particle>(
			L"Deferred", false,
			ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3::Zero, MassProperties(10.f, 10.f, 1.f),
			m_vTextureNames[i]);

		Vec3 vMyPos = GetTransform()->GetWorldPosition();
		vMyPos.z = 90.f;
		pParticle->GetTransform()->SetLocalPosition(vMyPos);

		Vec3 vRightNormal = VEC3_RIGHT_NORMAL;

		float fDegree = atan2(vDir.y, vDir.x) * 180.f / XM_PI;
		//if (fDegree < 0.f)
		//	fDegree += 180.f;

		float fForce = vDir.Length();

		int32 iRandomDegree = RANDOM(static_cast<int32>(fDegree - 15.f), static_cast<int32>(fDegree + 15.f));
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomAngularVelocity = RANDOM(-30, 30);
		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pParticle->Awake();
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, static_cast<float>(iRandomAngularVelocity)));
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(Conv::Vec3ToPxVec3(vRotatedVec * fForce));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pParticle, eSceneType));
	}
}

void ErodedKnight::ActivateDeadEvent(const Vec3& vDir)
{
	Monster::ActivateDeadEvent(vDir);
}

void ErodedKnight::ActivateDeadEvent()
{
	CreateExclamationEffectAndAddedToScene();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
	m_bDeadFlag = true;
}

void ErodedKnight::RemoveExclamationEffect()
{
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(m_pExclamation.lock(), SCENE_TYPE::DUNGEON));
}

void ErodedKnight::CreateExclamationEffectAndAddedToScene()
{
	shared_ptr<LocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<LocalEffect>(L"Forward");
	pLocalEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ExclamationEffect", L"..\\Resources\\Animation\\MonsterCommon\\sign_exclamation_mark.anim");
	pLocalEffect->GetAnimator()->AddAnimation(L"ExclamationEffect", pAnimation);
	pLocalEffect->GetAnimator()->Play(L"ExclamationEffect", true, -1);

	pLocalEffect->GetTransform()->SetParent(GetTransform());

	uint8 iDirection = static_cast<uint8>(GetDirection());
	pLocalEffect->GetTransform()->SetLocalPosition(Vec3(iDirection ? 15.f : -15.f, 90.f, 0.f));

	pLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));

	m_pExclamation = pLocalEffect;
}
