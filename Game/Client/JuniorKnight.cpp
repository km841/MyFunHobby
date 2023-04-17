#include "pch.h"
#include "JuniorKnight.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Particle.h"
#include "Scene.h"
#include "Scenes.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"

POOL_INIT(JuniorKnight);
JuniorKnight::JuniorKnight()
{
	m_Status.MonsterDefaultSetting();
}

JuniorKnight::~JuniorKnight()
{
}

void JuniorKnight::Awake()
{
	Monster::Awake();
}

void JuniorKnight::Start()
{
	Monster::Start();
}

void JuniorKnight::Update()
{
	Monster::Update();
	// 몬스터 AI 실행
}

void JuniorKnight::LateUpdate()
{
	Monster::LateUpdate();
}

void JuniorKnight::FinalUpdate()
{
	Monster::FinalUpdate();
}

void JuniorKnight::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
		//GetPhysical()->GetActor<PxRigidDynamic>()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
		//GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(PxVec3(0.f, 0.f, 0.f));
		//GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, 0.f));
	}

	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void JuniorKnight::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
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

void JuniorKnight::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void JuniorKnight::ScatterParticles()
{
	for (int32 i = 0; i < m_vTextureNames.size(); ++i)
	{
		shared_ptr<Particle> pParticle = GET_SINGLE(ObjectFactory)->CreateObjectFromPool<Particle>(L"Deferred", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE,
			Vec3(100.f, 100.f, 10.f), MassProperties(100.f, 100.f, 1.f), m_vTextureNames[i]);
		
		Vec3 vMyPos = GetTransform()->GetWorldPosition();
		vMyPos.z = 90.f;
		pParticle->GetTransform()->SetLocalPosition(vMyPos);

		Vec3 vRightNormal = VEC3_RIGHT_NORMAL;

		int32 iRandomDegree = RANDOM(1, 180);
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomAngular = RANDOM(60, 180);
		float fRandomAngularRadian = (iRandomAngular * XM_PI) / 180.f;

		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pParticle->Awake();
		pParticle->GetRigidBody()->SetVelocity(vRotatedVec * 400.f);
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, fRandomAngularRadian));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pParticle, eSceneType));
	}
}

