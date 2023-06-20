#include "pch.h"
#include "IncompletedAbyssMeteor.h"
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
#include "AnimationLocalEffect.h"

IncompletedAbyssMeteor::IncompletedAbyssMeteor(const Vec3& vPos)
	: m_fMaxDistance(1000.f)
	, m_fImpulse(1000.f)
	, m_vTargetPos(vPos)
{
}

IncompletedAbyssMeteor::~IncompletedAbyssMeteor()
{
}

void IncompletedAbyssMeteor::Awake()
{
	PlayerProjectile::Awake();
}

void IncompletedAbyssMeteor::Start()
{
	PlayerProjectile::Start();
}

void IncompletedAbyssMeteor::Update()
{
	PlayerProjectile::Update();
}

void IncompletedAbyssMeteor::LateUpdate()
{
	PlayerProjectile::LateUpdate();
}

void IncompletedAbyssMeteor::FinalUpdate()
{
	PlayerProjectile::FinalUpdate();
}

void IncompletedAbyssMeteor::CreateSmokeEffectAndAddedScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	pAnimationLocalEffect->SetDirection(GetDirection());
	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.y += 50.f;
	vPos.z -= -0.5f;

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPos);
	//pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 50.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Meteor_Despawn", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_meteor_incompleted_despawn.anim");
	pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Meteor_Despawn", pAnimation);
	pAnimationLocalEffect->GetAnimator()->Play(L"Meteor_Despawn", false);

	pAnimationLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}

void IncompletedAbyssMeteor::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		// vTargetPos와 가까운 타일인지 확인
		Vec3 vTilePos = pGameObject->GetTransform()->GetPhysicalPosition();
		Vec3 vDiff = m_vTargetPos - vTilePos;
		if (vDiff.Length() > 300.f)
			return;

		if (IsEnable())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			GET_SINGLE(CollisionManager)->SetForceInLayer(LAYER_TYPE::PARTICLE, vMyPos, Vec3(m_fMaxDistance, m_fMaxDistance, 0.f), Vec3(0.f, m_fImpulse, 0.f));
			GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(vMyPos, Vec3(m_fMaxDistance * 2.f, m_fMaxDistance * 2.f, 0.f), Vec3(0.f, m_fImpulse, 0.f), static_cast<float>(RANDOM(100, 200)), DAMAGE_TYPE::FROM_PLAYER_MAGIC);
		}

		Disable();
		CreateSmokeEffectAndAddedScene();
		GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(100.f, 300.f, 0.f));
		GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(300.f, 100.f, 0.f));
	}
}

void IncompletedAbyssMeteor::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
