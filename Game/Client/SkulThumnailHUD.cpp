#include "pch.h"
#include "SkulThumnailHUD.h"
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

SkulThumnailHUD::SkulThumnailHUD()
{
}

SkulThumnailHUD::~SkulThumnailHUD()
{
}

void SkulThumnailHUD::Awake()
{
	HUD::Awake();
	CreateAndAddCompletionEffectToScene();
}

void SkulThumnailHUD::Start()
{
	HUD::Start();
}

void SkulThumnailHUD::Update()
{
	HUD::Update();
}

void SkulThumnailHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void SkulThumnailHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void SkulThumnailHUD::CreateAndAddCompletionEffectToScene()
{
	//m_pCompletionEffect = make_shared<InterfaceEffect>();
	//m_pCompletionEffect->AddComponent(make_shared<Transform>());
	//m_pCompletionEffect->AddComponent(make_shared<Animator>());

	//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	//shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	//shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	//pMeshRenderer->SetMaterial(pMaterial);
	//pMeshRenderer->SetMesh(pMesh);

	//m_pCompletionEffect->GetTransform()->SetParent(GetTransform());

	//m_pCompletionEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 7.f, -10.f));
	//m_pCompletionEffect->AddComponent(pMeshRenderer);

	//SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	//shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Cooldown_Completion", L"..\\Resources\\Animation\\SkillBox\\cooldown_completion.anim");
	//m_pCompletionEffect->GetAnimator()->AddAnimation(L"Cooldown_Completion", pAnimation);

	//GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pCompletionEffect, eSceneType));
}
