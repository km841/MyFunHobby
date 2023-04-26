#include "pch.h"
#include "AbyssMeteor.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Resources.h"
#include "Scenes.h"
#include "Scene.h"
#include "GlobalEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "Physical.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "ObjectRemoveToSceneEvent.h"
#include "ForceOnObjectEvent.h"
#include "Engine.h"
#include "Clock.h"

shared_ptr<GlobalEffect> AbyssMeteor::s_pSmokeEffect = nullptr;
AbyssMeteor::AbyssMeteor()
	: m_fMaxDistance(500.f)
	, m_fImpulse(1000.f)
{
}

AbyssMeteor::~AbyssMeteor()
{
}

void AbyssMeteor::Awake()
{
	PlayerProjectile::Awake();
	if (nullptr == s_pSmokeEffect)
	{
		CreateSmokeEffectAndAddedScene();
	}
}

void AbyssMeteor::Start()
{
	PlayerProjectile::Start();
}

void AbyssMeteor::Update()
{
	PlayerProjectile::Update();
	GetRigidBody()->AddVelocity(AXIS::Y, -20.f * DELTA_TIME);
}

void AbyssMeteor::LateUpdate()
{
	PlayerProjectile::LateUpdate();
}

void AbyssMeteor::FinalUpdate()
{
	PlayerProjectile::FinalUpdate();
}

void AbyssMeteor::CreateSmokeEffectAndAddedScene()
{
	s_pSmokeEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GlobalEffect>(L"Forward");
	s_pSmokeEffect->GetTransform()->SetGlobalOffset(Vec2(20.f, 20.f));
	s_pSmokeEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"AbyssMeteor_Smoke", L"..\\Resources\\Animation\\HighWarlock\\charged_meteor_smoke.anim");
	s_pSmokeEffect->GetAnimator()->AddAnimation(L"AbyssMeteor_Smoke", pAnimation);
	s_pSmokeEffect->Awake();
	s_pSmokeEffect->Disable();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(s_pSmokeEffect, eSceneType));
}

void AbyssMeteor::EnableAndInitSmokeEffect()
{
	s_pSmokeEffect->GetTransform()->SetLocalPosition(Conv::PxVec3ToVec3(GetTransform()->GetPxTransform().p));
	s_pSmokeEffect->Enable();
	s_pSmokeEffect->GetAnimator()->Play(L"AbyssMeteor_Smoke", false);
}

void AbyssMeteor::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		if (IsEnable())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
		}

		Disable();
		EnableAndInitSmokeEffect();
		GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.15f, Vec3(100.f, 1000.f, 0.f));

		Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
		auto& vParticles = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::PARTICLE);
		for (auto& pParticle : vParticles)
		{
			Vec3 vParticlePos = pParticle->GetTransform()->GetPhysicalPosition();
			Vec3 vTargetVec = vParticlePos - vMyPos;

			if (vTargetVec.Length() < m_fMaxDistance)
			{
				float fRandomXImpulse = static_cast<float>(RANDOM(0, static_cast<int32>(m_fImpulse)));
				if (vTargetVec.x < 0.f)
					fRandomXImpulse = -fRandomXImpulse;

				PxVec3 vImpulse = PxVec3(fRandomXImpulse, m_fImpulse, 0.f);
				GET_SINGLE(EventManager)->AddEvent(make_unique<ForceOnObjectEvent>(pParticle, vImpulse));
			}
		}

		auto& vMonsters = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::MONSTER);
		for (auto& pMonster : vMonsters)
		{
			Vec3 vMonsterPos = pMonster->GetTransform()->GetPhysicalPosition();
			Vec3 vTargetVec = vMonsterPos - vMyPos;

			if (vTargetVec.Length() < m_fMaxDistance)
			{
				float fRandomXImpulse = static_cast<float>(RANDOM(0, 100));
				if (vTargetVec.x < 0.f)
					fRandomXImpulse = -fRandomXImpulse;

				PxVec3 vImpulse = PxVec3(fRandomXImpulse, 200.f, 0.f);

				static_pointer_cast<Monster>(pMonster)->FlagAsAttacked();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ForceOnObjectEvent>(pMonster, vImpulse));
			}
		}
	}
}

void AbyssMeteor::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{

}
