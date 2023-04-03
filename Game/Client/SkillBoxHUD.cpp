#include "pch.h"
#include "SkillBoxHUD.h"
#include "GlobalEffect.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animation.h"
#include "Animator.h"
#include "Resources.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"

SkillBoxHUD::SkillBoxHUD()
{
}

SkillBoxHUD::~SkillBoxHUD()
{
}

void SkillBoxHUD::Awake()
{
	HUD::Awake();
	// 이펙트 ui 추가
	//m_pGlobalEffect = make_shared<GlobalEffect>();
	//m_pGlobalEffect->AddComponent(make_shared<Transform>());
	//m_pGlobalEffect->AddComponent(make_shared<Animator>());

	//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Cooldown");
	//shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	//shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//pMeshRenderer->SetMaterial(pMaterial);
	//pMeshRenderer->SetMesh(pMesh);

	//m_pGlobalEffect->AddComponent(pMeshRenderer);

	//// 애니메이션 추가
	//GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pGlobalEffect));
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
