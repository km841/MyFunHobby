#include "pch.h"
#include "InterfaceManager.h"
#include "Interface.h"

#include "DialogueUI.h"
#include "inventoryUI.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"

#include "Resources.h"

#include "InventoryUI.h"
#include "MousePointerHUD.h"
#include "EndingHUD.h"

#include "PlayerHitHUD.h"
#include "HealthBarHUD.h"
#include "PlayerInterfaceHUD.h"
#include "SkulThumnailHUD.h"
#include "PlayerSkulThumnailScript.h"
#include "PlayerHealthBarShowScript.h"
#include "SkillBoxHUD.h"
#include "PlayerSkillShowScript.h"
#include "UI.h"
#include "HUD.h"
#include "ObjectFactory.h"
#include "BaseCampOpeningHUD.h"
#include "PlayerSecondSkillFrameHUD.h"
#include "DropItemHUD.h"
#include "DropSkulHUD.h"
#include "ClobberHUD.h"
#include "PlayerClubberShowScript.h"
#include "BossOpeningHUD.h"
#include "ChapterBossHPHUD.h"
#include "ViceBossHPHUD.h"
#include "SwapSkulHUD.h"
#include "PlayerSwapSkulShowScript.h"


void InterfaceManager::Init()
{
	CreateUI();
	CreateHUD();
}

void InterfaceManager::Destroy()
{
	for (auto& pInterface : m_mInterfaceMap)
	{
		pInterface.second->Destroy();
	}
}

shared_ptr<Interface> InterfaceManager::Get(INTERFACE_TYPE eInterfaceType)
{
	auto iter = m_mInterfaceMap.find(eInterfaceType);
	assert(iter != m_mInterfaceMap.end());
	return iter->second;
}

shared_ptr<UI> InterfaceManager::Get(UI_TYPE eUIType)
{
	auto iter = m_mInterfaceMap.find(static_cast<INTERFACE_TYPE>(eUIType));
	assert(iter != m_mInterfaceMap.end());
	return static_pointer_cast<UI>(iter->second);
}

shared_ptr<HUD> InterfaceManager::Get(HUD_TYPE eHUDType)
{
	uint8 iIndex = static_cast<uint8>(eHUDType);
	auto iter = m_mInterfaceMap.find(static_cast<INTERFACE_TYPE>(iIndex + UI_MAX_COUNT));
	assert(iter != m_mInterfaceMap.end());
	return static_pointer_cast<HUD>(iter->second);
}

void InterfaceManager::CreateUI()
{
	// Dialogue UI
	{
		shared_ptr<DialogueUI> pDialogueUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DialogueUI>(L"Forward", L"..\\Resources\\Texture\\UI\\UI_Dialog_Renew.png");
		pDialogueUI->SetFrustum(false);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pDialogueUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 280.f, 40.f));
		m_mInterfaceMap[INTERFACE_TYPE::DIALOGUE] = pDialogueUI;
	}

	// Inventory UI
	{
		shared_ptr<InventoryUI> pInventoryUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<InventoryUI>(L"Forward", L"..\\Resources\\Texture\\UI\\Inventory\\UI_Inventory_Frame_Hardmode.png");
		pInventoryUI->SetFrustum(false);
		pInventoryUI->Disable();

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pInventoryUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 30.f));
		m_mInterfaceMap[INTERFACE_TYPE::INVENTORY] = pInventoryUI;
	}
}

void InterfaceManager::CreateHUD()
{
	shared_ptr<PlayerInterfaceHUD> pInterfaceHUD = nullptr;
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	
	// Player Interface HUD
	{
		pInterfaceHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<PlayerInterfaceHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_Player_Normal_Frame.tga");
		pInterfaceHUD->SetFrustum(false);

		pInterfaceHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 420.f, fHeight / 2.f - 270.f, 50.f));
		pInterfaceHUD->GetTransform()->SetLocalScale(Vec3(203.f, 66.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_INTERFACE] = pInterfaceHUD;
	}

	// Second Skill Frame
	{
		shared_ptr<PlayerSecondSkillFrameHUD> pSecondSkillFrameHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<PlayerSecondSkillFrameHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_Player_Skill2_Frame.png");
		pSecondSkillFrameHUD->SetFrustum(false);

		pSecondSkillFrameHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		pSecondSkillFrameHUD->GetTransform()->SetLocalPosition(Vec3(-3.f, 10.f, -9.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SECOND_SKILL_FRAME] = pSecondSkillFrameHUD;
	}

	// Skul Thumnail HUD
	{
		shared_ptr<SkulThumnailHUD> pSkulThumnailHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkulThumnailHUD>(L"Cooldown");
		pSkulThumnailHUD->SetFrustum(false);

		pSkulThumnailHUD->AddComponent(make_shared<PlayerSkulThumnailScript>(pSkulThumnailHUD));
		pSkulThumnailHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		pSkulThumnailHUD->GetTransform()->SetLocalPosition(Vec3(-145.f, 18.f, -10.f));
		pSkulThumnailHUD->GetTransform()->SetLocalScale(Vec3(45.f, 45.f, 0.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKUL_THUMNAIL] = pSkulThumnailHUD;
	}

	// Skul Swap HUD
	{
		shared_ptr<SwapSkulHUD> pSwapSkulHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SwapSkulHUD>(L"Forward");
		pSwapSkulHUD->SetFrustum(false);
		pSwapSkulHUD->AddComponent(make_shared<PlayerSwapSkulShowScript>());
		pSwapSkulHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		pSwapSkulHUD->GetTransform()->SetLocalPosition(Vec3(-170.f, -18.f, -11.f));
		pSwapSkulHUD->GetTransform()->SetLocalScale(Vec3(20.f, 20.f, 0.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKUL_SWAP] = pSwapSkulHUD;
	}

	// Health Bar HUD
	{
		shared_ptr<HealthBarHUD> pHealthBarHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HealthBarHUD>(L"HP", L"..\\Resources\\Texture\\HUD\\HealthBar\\HUD_Player_HealthBar.tga");
		pHealthBarHUD->SetFrustum(false);

		pHealthBarHUD->AddComponent(make_shared<PlayerHealthBarShowScript>(pHealthBarHUD));
		pHealthBarHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		pHealthBarHUD->GetTransform()->SetLocalPosition(Vec3(1.f, -32.5f, -10.f));
		pHealthBarHUD->GetTransform()->SetLocalScale(Vec3(115.f, 8.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_HEALTH_BAR] = pHealthBarHUD;
	}

	// First Skill Box HUD
	{
		shared_ptr<SkillBoxHUD> pSkillBoxHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkillBoxHUD>(L"Cooldown", L"", SKILL_INDEX::FIRST);
		pSkillBoxHUD->SetFrustum(false);

		pSkillBoxHUD->AddComponent(make_shared<PlayerSkillShowScript>(pSkillBoxHUD, SKILL_INDEX::FIRST));
		pSkillBoxHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		pSkillBoxHUD->GetTransform()->SetLocalPosition(Vec3(-63.f, 11.5f, -10.f));
		pSkillBoxHUD->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKILL_BOX_FIRST] = pSkillBoxHUD;
	}

	// Second Skill Box HUD
	{
		shared_ptr<SkillBoxHUD> pSkillBoxHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkillBoxHUD>(L"Cooldown", L"", SKILL_INDEX::SECOND);
		pSkillBoxHUD->SetFrustum(false);

		pSkillBoxHUD->AddComponent(make_shared<PlayerSkillShowScript>(pSkillBoxHUD, SKILL_INDEX::SECOND));
		pSkillBoxHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		pSkillBoxHUD->GetTransform()->SetLocalPosition(Vec3(-1.5f, 11.5f, -10.f));
		pSkillBoxHUD->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKILL_BOX_SECOND] = pSkillBoxHUD;
	}

	// Player Hit HUD
	{
		shared_ptr<PlayerHitHUD> pPlayerHitHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<PlayerHitHUD>(L"Forward");
		pPlayerHitHUD->SetFrustum(false);
		pPlayerHitHUD->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"PlayerHit", L"..\\Resources\\Animation\\Player\\player_hit.anim");
		pPlayerHitHUD->GetAnimator()->AddAnimation(L"PlayerHit", pAnimation);

		pPlayerHitHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 80.f));
		
		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_HIT] = pPlayerHitHUD;
	}

	// Mouse Pointer HUD
	{
		shared_ptr<MousePointerHUD> pMousePointerHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MousePointerHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\Mouse_Cursor.png");
		pMousePointerHUD->SetFrustum(false);
		pMousePointerHUD->GetTransform()->SetLocalScale(Vec3(10.5f, 10.5f, 1.f));
		m_mInterfaceMap[INTERFACE_TYPE::MOUSE_POINTER] = pMousePointerHUD;
	}

	// BaseCamp Opening HUD
	{
		shared_ptr<BaseCampOpeningHUD> pOpeningHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<BaseCampOpeningHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\Dungeon\\Ch3\\Image_Ch3_BaseCamp_OpeningUI.png");
		pOpeningHUD->SetFrustum(false);
		pOpeningHUD->Disable();
		pOpeningHUD->GetTransform()->SetLocalPosition(Vec3(800.f, 450.f, 50.f));
		pOpeningHUD->GetTransform()->SetLocalScale(Vec3(212.f, 125.f, 1.f));
		m_mInterfaceMap[INTERFACE_TYPE::BASECAMP_OPENING] = pOpeningHUD;
	}

	// Drop Item First HUD
	{
		shared_ptr<DropItemHUD> pDropItemHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DropItemHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupItem.png");
		pDropItemHUD->SetFrustum(false);
		pDropItemHUD->Disable();

		m_mInterfaceMap[INTERFACE_TYPE::DROP_ITEM_FIRST] = pDropItemHUD;
	}

	// Drop Item Second HUD
	{
		shared_ptr<DropItemHUD> pDropItemHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DropItemHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupItem.png");
		pDropItemHUD->SetFrustum(false);
		pDropItemHUD->Disable();

		m_mInterfaceMap[INTERFACE_TYPE::DROP_ITEM_SECOND] = pDropItemHUD;
	}

	// Drop Skul HUD
	{
		shared_ptr<DropSkulHUD> pDropSkulHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DropSkulHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupSkul.png");
		pDropSkulHUD->SetFrustum(false);
		pDropSkulHUD->Disable();

		m_mInterfaceMap[INTERFACE_TYPE::DROP_SKUL] = pDropSkulHUD;
	}

	// Clobber HUD
	{
		shared_ptr<ClobberHUD> pClobberHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ClobberHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_Player_Clobber_2.png");
		pClobberHUD->SetFrustum(false);
		pClobberHUD->GetTransform()->SetLocalPosition(Vec3(fWidth - 190.f, fHeight / 2.f - 305.f, 50.f));
		pClobberHUD->AddComponent(make_shared<PlayerClubberShowScript>());

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_CLOBBER] = pClobberHUD;
	}

	// Boss Opening HUD
	{
		shared_ptr<BossOpeningHUD> pBossOpeningHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<BossOpeningHUD>(L"Forward");
		pBossOpeningHUD->SetFrustum(false);
		pBossOpeningHUD->Disable();

		m_mInterfaceMap[INTERFACE_TYPE::BOSS_OPENING] = pBossOpeningHUD;
	}

	// Chapter Boss HP HUD
	{
		shared_ptr<ChapterBossHPHUD> pChapterBossHPHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ChapterBossHPHUD>(L"Forward");
		pChapterBossHPHUD->SetFrustum(false);
		pChapterBossHPHUD->Disable();
		pChapterBossHPHUD->GetTransform()->SetLocalScale(Vec3(356.f, 68.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::BOSS_HP] = pChapterBossHPHUD;
	}

	// Vice Boss HP HUD
	{
		shared_ptr<ViceBossHPHUD> pViceBossHPHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ViceBossHPHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\Dungeon\\Ch3\\Image_Ch3_ViceBoss_HPBar.png");
		pViceBossHPHUD->SetFrustum(false);
		pViceBossHPHUD->Disable();
		pViceBossHPHUD->GetTransform()->SetLocalScale(Vec3(356.f, 68.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::VICE_BOSS_HP] = pViceBossHPHUD;
	}

	// Ending HUD
	{
		shared_ptr<EndingHUD> pEndingHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<EndingHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\Title_Logo_White.png");
		pEndingHUD->SetFrustum(false);
		pEndingHUD->Disable();
		pEndingHUD->GetTransform()->SetLocalPosition(Vec3(800.f, 450.f, 30.f));
		pEndingHUD->GetTransform()->SetLocalScale(Vec3(319.f, 173.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::ENDING] = pEndingHUD;
	}

	
	
}
