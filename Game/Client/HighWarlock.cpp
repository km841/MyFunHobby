#include "pch.h"
#include "HighWarlock.h"
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
#include "ObjectFactory.h"
#include "AnimationGlobalEffect.h"

HighWarlock::HighWarlock(const SkulInfo& skulInfo)
	: Skul(skulInfo)
{
}

void HighWarlock::Awake()
{
	Skul::Awake();
	CreateAbyssFieldAndAddedToScene();
	CreateTrailEffectAndAddedToScene();
	CreateChargedEffectAndAddedToScene();
}

void HighWarlock::Start()
{
	Skul::Start();
}

void HighWarlock::Update()
{
	Skul::Update();

}

void HighWarlock::LateUpdate()
{
	Skul::LateUpdate();
	if (m_pAbyssField->GetTimer().IsFinished())
		m_pAbyssField->Disable();

	TrailAndChargedEffectPositionUpdate();
}

void HighWarlock::FinalUpdate()
{
	Skul::FinalUpdate();
}

void HighWarlock::ActiveAbyssField()
{
	m_pAbyssField->GetTimer().Start();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	m_pAbyssField->GetTransform()->SetLocalPosition(vPlayerPos);
	m_pAbyssField->Enable();
	m_pAbyssField->GetAnimator()->Play(L"HighWarlock_AbyssField");
}

void HighWarlock::DeActiveAbyssField()
{
	m_pAbyssField->Disable();
}

void HighWarlock::EnableAndInitTrailEffect()
{
	m_pTrailEffect->Enable();
	m_pTrailEffect->GetAnimator()->Play(L"HighWarlock_Trail");
}

void HighWarlock::DisableTrailEffect()
{
	m_pTrailEffect->Disable();
}

void HighWarlock::EnableAndInitChargedEffect()
{
	m_pChargedEffect->Enable();
	m_pChargedEffect->GetAnimator()->Play(L"HighWarlock_Charged", false);
}

void HighWarlock::CreateAbyssFieldAndAddedToScene()
{
	m_pAbyssField = make_shared<GlobalEffect>(5.f);
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pAbyssField->AddComponent(make_shared<Transform>());
	m_pAbyssField->GetTransform()->SetGlobalOffset(Vec2(0.f, 60.f));

	m_pAbyssField->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_AbyssField", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_abyssfield.anim");
	m_pAbyssField->GetAnimator()->AddAnimation(L"HighWarlock_AbyssField", pAnimation);

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	m_pAbyssField->AddComponent(pMeshRenderer);

	m_pAbyssField->Awake();
	m_pAbyssField->Disable();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pAbyssField, eSceneType));
}

void HighWarlock::CreateTrailEffectAndAddedToScene()
{
	m_pTrailEffect = make_shared<GlobalEffect>();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pTrailEffect->AddComponent(make_shared<Transform>());
	m_pTrailEffect->GetTransform()->SetGlobalOffset(Vec2(20.f, 20.f));

	m_pTrailEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Trail", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_trail.anim");
	m_pTrailEffect->GetAnimator()->AddAnimation(L"HighWarlock_Trail", pAnimation);

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	m_pTrailEffect->AddComponent(pMeshRenderer);

	m_pTrailEffect->Awake();
	m_pTrailEffect->Disable();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pTrailEffect, eSceneType));
}

void HighWarlock::CreateChargedEffectAndAddedToScene()
{
	m_pChargedEffect = make_shared<GlobalEffect>();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pChargedEffect->AddComponent(make_shared<Transform>());
	m_pChargedEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 60.f));

	m_pChargedEffect->AddComponent(make_shared<Animator>());

	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Charged", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_charged.anim");
		m_pChargedEffect->GetAnimator()->AddAnimation(L"HighWarlock_Charged", pAnimation);
	}

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	m_pChargedEffect->AddComponent(pMeshRenderer);

	m_pChargedEffect->Awake();
	m_pChargedEffect->Disable();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pChargedEffect, eSceneType));
}

void HighWarlock::CreateCompletedSmokeAndAddedToScene()
{
	shared_ptr<AnimationGlobalEffect> pAnimGlobalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationGlobalEffect>(L"Forward");
	
	pAnimGlobalEffect->GetTransform()->SetParent(GetTransform());
	pAnimGlobalEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -20.f));
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	pAnimGlobalEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Completed", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_charge_complete.anim");
	pAnimGlobalEffect->GetAnimator()->AddAnimation(L"HighWarlock_Completed", pAnimation);
	pAnimGlobalEffect->GetAnimator()->Play(L"HighWarlock_Completed", false);

	pAnimGlobalEffect->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimGlobalEffect, eSceneType));
}

void HighWarlock::TrailAndChargedEffectPositionUpdate()
{
	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	DIRECTION eDirection = GetDirection();

	switch (eDirection)
	{
	case DIRECTION::RIGHT:
		vPlayerPos.x += 5.f;

		break;
	case DIRECTION::LEFT:
		vPlayerPos.x += -30.f;
		break;
	}

	vPlayerPos.z -= 10.f;
	m_pTrailEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	vPlayerPos.z -= 5.f;
	vPlayerPos.y -= 5.f;
	m_pChargedEffect->GetTransform()->SetLocalPosition(vPlayerPos);
}
