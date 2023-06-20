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
#include "CollisionManager.h"

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
	GetRigidBody()->AddVelocity(AXIS::Y, -20.f * OBJECT_DELTA_TIME);
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
			GET_SINGLE(Scenes)->GetActiveScene()->RegisterSceneEvent(EVENT_TYPE::SCENE_FADE_EVENT, static_cast<uint8>(SCENE_FADE_EFFECT::WHITE_FADE_IN), 0.5f);
			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			GET_SINGLE(CollisionManager)->SetForceInLayer(LAYER_TYPE::PARTICLE, vMyPos, Vec3(m_fMaxDistance, m_fMaxDistance, 0.f), Vec3(0.f, m_fImpulse, 0.f));
			GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(vMyPos, Vec3(m_fMaxDistance * 2.f, m_fMaxDistance * 2.f, 0.f), Vec3(0.f, m_fImpulse, 0.f), RANDOM(100, 200), DAMAGE_TYPE::FROM_PLAYER_MAGIC);
		}

		Disable();
		EnableAndInitSmokeEffect();
		GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(100.f, 1000.f, 0.f));
		GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(1000.f, 100.f, 0.f));
	}
}

void AbyssMeteor::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{

}
