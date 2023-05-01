#include "pch.h"
#include "InventoryUI.h"
#include "SkulInfoUI.h"
#include "ItemInfoUI.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "InfoUI.h"
#include "ArtifactInfoUI.h"
#include "DarkAbilInfoUI.h"
#include "DetailInfoUI.h"
#include "Engine.h"

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

	if (IsEnable())
	{
		DrawInventorySubjectForElements();
	}
}

void InventoryUI::LateUpdate()
{
	UI::LateUpdate();
}

void InventoryUI::FinalUpdate()
{
	UI::FinalUpdate();
}

void InventoryUI::Enable()
{
	for (auto& pInfoUI : m_vSkulInfoUI)
		pInfoUI->Enable();

	for (auto& pInfoUI : m_vArtifactInfoUI)
		pInfoUI->Enable();

	for (auto& pInfoUI : m_vItemInfoUI)
		pInfoUI->Enable();

	for (auto& pInfoUI : m_vDarkAbilInfoUI)
		pInfoUI->Enable();

	if (m_pDetailInfoUI)
		m_pDetailInfoUI->Enable();

	GameObject::Enable();
}

void InventoryUI::Disable()
{
	for (auto& pInfoUI : m_vSkulInfoUI)
		pInfoUI->Disable();

	for (auto& pInfoUI : m_vArtifactInfoUI)
		pInfoUI->Disable();

	for (auto& pInfoUI : m_vItemInfoUI)
		pInfoUI->Disable();

	for (auto& pInfoUI : m_vDarkAbilInfoUI)
		pInfoUI->Disable();

	if (m_pDetailInfoUI)
		m_pDetailInfoUI->Disable();

	GameObject::Disable();
}

void InventoryUI::CreateChildUIAndAddedToScene()
{
	CreateDetailInfoUI();
	CreateSkulInfoUI();
	CreateArtifactInfoUI();
	CreateItemInfoUI();
	CreateDarkAbilInfoUI();
}

void InventoryUI::CreateSkulInfoUI()
{
	// First Skul Info
	{
		shared_ptr<SkulInfoUI> pSkulInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkulInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pSkulInfo->GetTransform()->SetParent(GetTransform());
		pSkulInfo->GetTransform()->SetLocalPosition(Vec3(-278.f, 218.1f, -10.f));
		pSkulInfo->SetSkulIndex(SKUL_INDEX::FIRST);
		pSkulInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pSkulInfo->Awake();
		pSkulInfo->Disable();
		m_vSkulInfoUI.push_back(pSkulInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSkulInfo, eSceneType));
	}
	
	// Second Skul Info
	{
		shared_ptr<SkulInfoUI> pSkulInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkulInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pSkulInfo->GetTransform()->SetParent(GetTransform());
		pSkulInfo->GetTransform()->SetLocalPosition(Vec3(-194.f, 218.1f, -10.f));
		pSkulInfo->SetSkulIndex(SKUL_INDEX::SECOND);
		pSkulInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pSkulInfo->Awake();
		pSkulInfo->Disable();
		m_vSkulInfoUI.push_back(pSkulInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSkulInfo, eSceneType));
	}
}

void InventoryUI::CreateArtifactInfoUI()
{
	// Artifact Info
	{
		shared_ptr<ArtifactInfoUI> pArtifactInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ArtifactInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pArtifactInfo->GetTransform()->SetParent(GetTransform());
		pArtifactInfo->GetTransform()->SetLocalPosition(Vec3(-235.f, 114.f, -10.f));
		pArtifactInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pArtifactInfo->Awake();
		pArtifactInfo->Disable();
		m_vArtifactInfoUI.push_back(pArtifactInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pArtifactInfo, eSceneType));
	}
}

void InventoryUI::CreateItemInfoUI()
{
#pragma region Item Row 1
	// Item Info_1_1
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
				L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_1_1);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-320.5f, 10.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

	// Item Info_1_2
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_1_2);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-235.5f, 10.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

	// Item Info_1_3
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_1_3);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-150.5f, 10.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}
#pragma endregion
#pragma region Item Row 2
	// Item Info_2_1
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_2_1);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-320.5f, -55.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

	// Item Info_2_2
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_2_2);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-235.5f, -55.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

	// Item Info_2_3
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_2_3);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-150.5f, -55.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

#pragma endregion
#pragma region Item Row 3
	// Item Info_3_1
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_3_1);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-320.5f, -120.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

	// Item Info_3_2
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_3_2);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-235.5f, -120.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}

	// Item Info_3_3
	{
		shared_ptr<ItemInfoUI> pItemInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ItemInfoUI>(
			L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png", ITEM_PLACE::PLACE_3_3);
		pItemInfo->GetTransform()->SetParent(GetTransform());
		pItemInfo->GetTransform()->SetLocalPosition(Vec3(-150.5f, -120.f, -10.f));
		pItemInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pItemInfo->Awake();
		pItemInfo->Disable();
		m_vSkulInfoUI.push_back(pItemInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pItemInfo, eSceneType));
	}
#pragma endregion
}

void InventoryUI::CreateDarkAbilInfoUI()
{
	// DarkAbil Info_1
	{
		shared_ptr<DarkAbilInfoUI> pDarkAbilInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DarkAbilInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pDarkAbilInfo->GetTransform()->SetParent(GetTransform());
		pDarkAbilInfo->GetTransform()->SetLocalPosition(Vec3(-327.f, -222.5f, -10.f));
		pDarkAbilInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pDarkAbilInfo->Awake();
		pDarkAbilInfo->Disable();
		m_vDarkAbilInfoUI.push_back(pDarkAbilInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDarkAbilInfo, eSceneType));
	}

	// DarkAbil Info_2
	{
		shared_ptr<DarkAbilInfoUI> pDarkAbilInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DarkAbilInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pDarkAbilInfo->GetTransform()->SetParent(GetTransform());
		pDarkAbilInfo->GetTransform()->SetLocalPosition(Vec3(-267.f, -222.5f, -10.f));
		pDarkAbilInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pDarkAbilInfo->Awake();
		pDarkAbilInfo->Disable();
		m_vDarkAbilInfoUI.push_back(pDarkAbilInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDarkAbilInfo, eSceneType));
	}

	// DarkAbil Info_3
	{
		shared_ptr<DarkAbilInfoUI> pDarkAbilInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DarkAbilInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pDarkAbilInfo->GetTransform()->SetParent(GetTransform());
		pDarkAbilInfo->GetTransform()->SetLocalPosition(Vec3(-207.f, -222.5f, -10.f));
		pDarkAbilInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pDarkAbilInfo->Awake();
		pDarkAbilInfo->Disable();
		m_vDarkAbilInfoUI.push_back(pDarkAbilInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDarkAbilInfo, eSceneType));
	}

	// DarkAbil Info_4
	{
		shared_ptr<DarkAbilInfoUI> pDarkAbilInfo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DarkAbilInfoUI>(L"InventoryInfo", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		pDarkAbilInfo->GetTransform()->SetParent(GetTransform());
		pDarkAbilInfo->GetTransform()->SetLocalPosition(Vec3(-147.f, -222.5f, -10.f));
		pDarkAbilInfo->SetDetailInfoUI(m_pDetailInfoUI);

		pDarkAbilInfo->Awake();
		pDarkAbilInfo->Disable();
		m_vDarkAbilInfoUI.push_back(pDarkAbilInfo);
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDarkAbilInfo, eSceneType));
	}
}

void InventoryUI::CreateDetailInfoUI()
{
	// Detail Info
	{
		m_pDetailInfoUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DetailInfoUI>(L"Forward");
		m_pDetailInfoUI->GetTransform()->SetParent(GetTransform());
		m_pDetailInfoUI->GetTransform()->SetLocalPosition(Vec3(222.f, -75.f, -10.f));

		m_pDetailInfoUI->m_pInventoryUI = Conv::BaseToDeclare<InventoryUI>(shared_from_this());
		m_pDetailInfoUI->Awake();
		m_pDetailInfoUI->Disable();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pDetailInfoUI, eSceneType));
	}
}

void InventoryUI::DrawInventorySubjectForElements()
{
	FONT->DrawString(L"스컬", 23.f, Vec3(504.f, 798.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
	FONT->DrawString(L"정수", 23.f, Vec3(504.f, 667.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
	FONT->DrawString(L"아이템", 23.f, Vec3(504.f, 539.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
	FONT->DrawString(L"검은 능력", 23.f, Vec3(504.f, 249.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
}
