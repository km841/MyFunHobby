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
	
}

JuniorKnight::~JuniorKnight()
{
}

void JuniorKnight::Awake()
{
	Monster::Awake();
	m_Status.KnightMonsterDefaultSetting();


}

void JuniorKnight::Start()
{
	Monster::Start();
}

void JuniorKnight::Update()
{
	Monster::Update();
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

	if (LAYER_TYPE::PLAYER_PROJECTILE == pGameObject->GetLayerType())
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

void JuniorKnight::ScatterParticles(PARTICLE_DIRECTION eParticleDirection)
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

		int32 iRandomDegree = CalculateParticleDirectionToDegree(eParticleDirection);
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomAngularVelocity = RANDOM(-30, 30);
		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pParticle->Awake();
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, static_cast<float>(iRandomAngularVelocity)));
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(Conv::Vec3ToPxVec3(vRotatedVec * 800.f));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pParticle, eSceneType));
	}
}

void JuniorKnight::ActivateDeadEvent(PARTICLE_DIRECTION eParticleDirection)
{
	Monster::ActivateDeadEvent(eParticleDirection);
}

void JuniorKnight::ScatterParticles(const Vec3& vDir)
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

void JuniorKnight::ActivateDeadEvent(const Vec3& vDir)
{
	Monster::ActivateDeadEvent(vDir);
}

