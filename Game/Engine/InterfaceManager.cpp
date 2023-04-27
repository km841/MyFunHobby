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

#include "PlayerHitHUD.h"
#include "HealthBarHUD.h"
#include "PlayerInterfaceHUD.h"
#include "SkulThumnailHUD.h"
#include "PlayerSkulThumnailScript.h"
#include "PlayerHealthBarShowScript.h"
#include "SkillBoxHUD.h"
#include "PlayerFirstSkillShowScript.h"
#include "UI.h"
#include "HUD.h"
#include "ObjectFactory.h"

void InterfaceManager::Init()
{
	CreateUI();
	CreateHUD();
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
		shared_ptr<DialogueUI> pDialogueUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DialogueUI>(L"Forward", L"..\\Resources\\Texture\\UI\\UI_Dialog.tga");
		pDialogueUI->SetFrustum(false);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pDialogueUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 420.f, fHeight / 2.f - 270.f, 40.f));
		m_mInterfaceMap[INTERFACE_TYPE::DIALOGUE] = pDialogueUI;
	}

	// Inventory UI
	{
		shared_ptr<InventoryUI> pInventoryUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<InventoryUI>(L"Forward", L"..\\Resources\\Texture\\UI\\Inventory\\UI_Inventory_Frame_Hardmode.png");
		pInventoryUI->SetFrustum(false);
		pInventoryUI->Disable();

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pInventoryUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 40.f));
		m_mInterfaceMap[INTERFACE_TYPE::INVENTORY] = pInventoryUI;
	}
}

void InterfaceManager::CreateHUD()
{
	shared_ptr<PlayerInterfaceHUD> pInterfaceHUD = nullptr;
	
	// Player Interface HUD
	{
		pInterfaceHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<PlayerInterfaceHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_Player_Normal_Frame.tga");
		pInterfaceHUD->SetFrustum(false);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pInterfaceHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 420.f, fHeight / 2.f - 270.f, 80.f));
		pInterfaceHUD->GetTransform()->SetLocalScale(Vec3(203.f, 66.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_INTERFACE] = pInterfaceHUD;

	}

	// Skul Thumnail HUD
	{
		shared_ptr<SkulThumnailHUD> pSkulThumnailHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkulThumnailHUD>(L"Cooldown");
		pSkulThumnailHUD->SetFrustum(false);

		pSkulThumnailHUD->AddComponent(make_shared<PlayerSkulThumnailScript>(pSkulThumnailHUD));
		pSkulThumnailHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pSkulThumnailHUD->GetTransform()->SetLocalPosition(Vec3(-145.f, 18.f, -10.f));
		pSkulThumnailHUD->GetTransform()->SetLocalScale(Vec3(45.f, 45.f, 0.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKUL_THUMNAIL] = pSkulThumnailHUD;
	}

	// Health Bar HUD
	{
		shared_ptr<HealthBarHUD> pHealthBarHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HealthBarHUD>(L"HP", L"..\\Resources\\Texture\\HUD\\HealthBar\\HUD_Player_HealthBar.tga");
		pHealthBarHUD->SetFrustum(false);

		pHealthBarHUD->AddComponent(make_shared<PlayerHealthBarShowScript>(pHealthBarHUD));
		pHealthBarHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pHealthBarHUD->GetTransform()->SetLocalPosition(Vec3(1.f, -32.5f, -10.f));
		pHealthBarHUD->GetTransform()->SetLocalScale(Vec3(115.f, 8.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_HEALTH_BAR] = pHealthBarHUD;
	}

	// Skill Box HUD
	{
		shared_ptr<SkillBoxHUD> pSkillBoxHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<SkillBoxHUD>(L"Cooldown");
		pSkillBoxHUD->SetFrustum(false);

		pSkillBoxHUD->AddComponent(make_shared<PlayerFirstSkillShowScript>(pSkillBoxHUD));
		pSkillBoxHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pSkillBoxHUD->GetTransform()->SetLocalPosition(Vec3(-63.f, 11.5f, -10.f));
		pSkillBoxHUD->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKILL_BOX_FIRST] = pSkillBoxHUD;
	}

	// Player Hit HUD
	{
		shared_ptr<PlayerHitHUD> pPlayerHitHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<PlayerHitHUD>(L"Forward");
		pPlayerHitHUD->SetFrustum(false);
		pPlayerHitHUD->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"PlayerHit", L"..\\Resources\\Animation\\Player\\player_hit.anim");
		pPlayerHitHUD->GetAnimator()->AddAnimation(L"PlayerHit", pAnimation);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

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

}
