#include "pch.h"
#include "InventoryUI.h"
#include "SkulInfoUI.h"
#include "ItemInfoUI.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"

InventoryUI::InventoryUI()
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Awake()
{
	UI::Awake();
	CreateChildUIAndAddedToScene();
}

void InventoryUI::Start()
{
	UI::Start();
}

void InventoryUI::Update()
{
	UI::Update();
}

void InventoryUI::LateUpdate()
{
	UI::LateUpdate();
}

void InventoryUI::FinalUpdate()
{
	UI::FinalUpdate();
}

void InventoryUI::CreateChildUIAndAddedToScene()
{
	CreateSkulInfoUI();
	CreateItemInfoUI();
}

void InventoryUI::CreateSkulInfoUI()
{
	// First Skul Info
	{
		shared_ptr<SkulInfoUI> pSkulInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkulInfoUI>(L"Forward", L"..\\Resources\\Texture\\UI\\Inventory\\InventorySlot.png");
		pSkulInfo->GetTransform()->SetParent(GetTransform());
		pSkulInfo->GetTransform()->SetLocalPosition(Vec3(-278.f, 217.5f, -10.f));

		pSkulInfo->Awake();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSkulInfo, eSceneType));
	}
	

	// Second Skul Info
	{
		shared_ptr<SkulInfoUI> pSkulInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkulInfoUI>(L"Forward", L"..\\Resources\\Texture\\UI\\Inventory\\InventorySlot.png");
		pSkulInfo->GetTransform()->SetParent(GetTransform());
		pSkulInfo->GetTransform()->SetLocalPosition(Vec3(-193.5f, 217.5f, -10.f));

		pSkulInfo->Awake();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSkulInfo, eSceneType));
	}

}

void InventoryUI::CreateItemInfoUI()
{
}
