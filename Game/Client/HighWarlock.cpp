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

HighWarlock::HighWarlock()
	: Skul(SKUL_GRADE::UNIQUE)
{
}

void HighWarlock::Awake()
{
	Skul::Awake();
	CreateEffectAndAddedToScene();
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

void HighWarlock::CreateEffectAndAddedToScene()
{
	m_pAbyssField = make_shared<GlobalEffect>(5.f);
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pAbyssField->AddComponent(make_shared<Transform>());
	m_pAbyssField->GetTransform()->SetGlobalOffset(Vec2(0.f, 40.f));

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