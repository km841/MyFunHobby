#include "pch.h"
#include "SkillBoxHUD.h"
#include "InterfaceEffect.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animation.h"
#include "Animator.h"
#include "Resources.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectFactory.h"

SkillBoxHUD::SkillBoxHUD(SKILL_INDEX eSkillIndex)
	: m_eSkillIndex(eSkillIndex)
{
}

SkillBoxHUD::~SkillBoxHUD()
{
}

void SkillBoxHUD::Awake()
{
	if (!IsAwake())
	{
		HUD::Awake();
		CreateAndAddCompletionEffectToScene();
		CreateHotKeyHUDAndAddedToScene();
	}
}

void SkillBoxHUD::Start()
{
	HUD::Start();
}

void SkillBoxHUD::Update()
{
	HUD::Update();
}

void SkillBoxHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void SkillBoxHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void SkillBoxHUD::Enable()
{
	GameObject::Enable();
	if (m_pHotKeyHUD)
		m_pHotKeyHUD->Enable();
	
}

void SkillBoxHUD::Disable()
{
	if (m_pHotKeyHUD)
		m_pHotKeyHUD->Disable();

	GameObject::Disable();
}

void SkillBoxHUD::CreateAndAddCompletionEffectToScene()
{
	m_pCompletionEffect = make_shared<InterfaceEffect>();
	m_pCompletionEffect->AddComponent(make_shared<Transform>());
	m_pCompletionEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	m_pCompletionEffect->GetTransform()->SetParent(GetTransform());

	m_pCompletionEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 7.f, -10.f));
	m_pCompletionEffect->AddComponent(pMeshRenderer);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Cooldown_Completion", L"..\\Resources\\Animation\\SkillBox\\cooldown_completion.anim");
	m_pCompletionEffect->GetAnimator()->AddAnimation(L"Cooldown_Completion", pAnimation);

	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pCompletionEffect, eSceneType));
}

void SkillBoxHUD::CreateHotKeyHUDAndAddedToScene()
{
	switch (m_eSkillIndex)
	{
	case SKILL_INDEX::FIRST:
		m_pHotKeyHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HUD>(L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_A.png");
		break;
	case SKILL_INDEX::SECOND:
		m_pHotKeyHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HUD>(L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_S.png");
		break;
	}
	
	assert(m_pHotKeyHUD);
	m_pHotKeyHUD->GetTransform()->SetParent(GetTransform());
	m_pHotKeyHUD->GetTransform()->SetLocalPosition(Vec3(0.f, 27.f, -1.f));

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHotKeyHUD, eSceneType));
}

void SkillBoxHUD::PlayCompletionAnimation()
{
	m_pCompletionEffect->Enable();
	m_pCompletionEffect->GetAnimator()->Play(L"Cooldown_Completion", false);
}
