#include "pch.h"
#include "SwapSkulHUD.h"
#include "Player.h"
#include "Skul.h"
#include "ObjectFactory.h"
#include "Scene.h"
#include "Scenes.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"

SwapSkulHUD::SwapSkulHUD()
{
}

SwapSkulHUD::~SwapSkulHUD()
{
}

void SwapSkulHUD::Awake()
{
	HUD::Awake();
	if (!m_pSpaceHUD.lock())
		CreateSpaceKeyHUDAndAddedToScene();
}

void SwapSkulHUD::Start()
{
	HUD::Start();
}

void SwapSkulHUD::Update()
{
	HUD::Update();
}

void SwapSkulHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void SwapSkulHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void SwapSkulHUD::Enable()
{
	GameObject::Enable();
	m_pSpaceHUD.lock()->Enable();
}

void SwapSkulHUD::Disable()
{
	m_pSpaceHUD.lock()->Disable();
	GameObject::Disable();
}

void SwapSkulHUD::CreateSpaceKeyHUDAndAddedToScene()
{
	shared_ptr<HUD> pSpaceHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HUD>(L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_Space.png");
	pSpaceHUD->SetFrustum(false);
	pSpaceHUD->GetTransform()->SetParent(GetTransform());

	pSpaceHUD->GetTransform()->SetLocalPosition(Vec3(0.f, -20.f, -1.f));
	pSpaceHUD->GetTransform()->SetLocalScale(Vec3(20.f, 9.f, 1.f));

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSpaceHUD, eSceneType));

	m_pSpaceHUD = pSpaceHUD;
}
