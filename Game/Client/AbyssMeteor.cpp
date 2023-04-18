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

shared_ptr<GlobalEffect> AbyssMeteor::s_pSmokeEffect = nullptr;
AbyssMeteor::AbyssMeteor()
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
	s_pSmokeEffect = GET_SINGLE(ObjectFactory)->CreateObject<GlobalEffect>(L"Forward");
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
		Disable();
		EnableAndInitSmokeEffect();
		Vec3 vMyPos = GetTransform()->GetPhysicalPosition();

		auto& vParticles = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::PARTICLE);
		for (auto& pParticle : vParticles)
		{
			Vec3 vParticlePos = pParticle->GetTransform()->GetPhysicalPosition();
			Vec3 vTargetVec = vParticlePos - vMyPos;

			if (vTargetVec.Length() < 1000.f)
			{
				float fRandomXImpulse = static_cast<float>(RANDOM(0, 1000));
				if (vTargetVec.x < 0.f)
					fRandomXImpulse = -fRandomXImpulse;

				PxVec3 vImpulse = PxVec3(fRandomXImpulse, 1000.f, 0.f);

				PxRigidBodyExt::addForceAtPos(
					*pParticle->GetPhysical()->GetActor<PxRigidDynamic>(),
					vImpulse,
					Conv::Vec3ToPxVec3(vParticlePos),
					PxForceMode::eIMPULSE
				);

				int32 iRandomAngular = RANDOM(-1000, 1000);
				float fRandomAngularRadian = (iRandomAngular * XM_PI) / 180.f;
				pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, fRandomAngularRadian));

			}
		}
		//GetTransform()->SetPhysicalPosition(Vec3(100.f, 100.f, 0.f));
		//SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		//GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
	}
}

void AbyssMeteor::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
