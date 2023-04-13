#include "pch.h"
#include "InterfaceManager.h"
#include "Interface.h"

#include "DialogueUI.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Transform.h"

#include "Resources.h"

#include "HealthBarHUD.h"
#include "PlayerInterfaceHUD.h"
#include "SkulThumnailHUD.h"
#include "PlayerSkulThumnailScript.h"
#include "PlayerHealthBarShowScript.h"
#include "SkillBoxHUD.h"
#include "PlayerFirstSkillShowScript.h"
#include "UI.h"
#include "HUD.h"

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
		shared_ptr<DialogueUI> pDialogueUI = make_shared<DialogueUI>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"DialogueUI", L"..\\Resources\\Texture\\UI\\UI_Dialog.tga");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pDialogueUI->AddComponent(pMeshRenderer);
		pDialogueUI->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pDialogueUI->GetTransform()->SetLocalScale(pTexture->GetTexSize());
		//pDialogueUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 420.f, fHeight / 2.f - 270.f, 40.f));
		m_mInterfaceMap[INTERFACE_TYPE::DIALOGUE] = pDialogueUI;
	}
}

void InterfaceManager::CreateHUD()
{
	shared_ptr<PlayerInterfaceHUD> pInterfaceHUD = nullptr;
	// Player Interface HUD
	{
		pInterfaceHUD = make_shared<PlayerInterfaceHUD>();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"PlayerInterfaceHUD", L"..\\Resources\\Texture\\HUD\\HUD_Player_Normal_Frame.tga");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pInterfaceHUD->AddComponent(pMeshRenderer);
		pInterfaceHUD->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pInterfaceHUD->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f - 420.f, fHeight / 2.f - 270.f, 80.f));
		pInterfaceHUD->GetTransform()->SetLocalScale(Vec3(203.f, 66.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_INTERFACE] = pInterfaceHUD;

	}

	// Skul Thumnail HUD
	{
		shared_ptr<SkulThumnailHUD> pSkulThumnailHUD = make_shared<SkulThumnailHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Cooldown")->Clone();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pSkulThumnailHUD->AddComponent(pMeshRenderer);
		pSkulThumnailHUD->AddComponent(make_shared<Transform>());
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
		shared_ptr<HealthBarHUD> pHealthBarHUD = make_shared<HealthBarHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"HP")->Clone();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HealthBarHUD", L"..\\Resources\\Texture\\HUD\\HealthBar\\HUD_Player_HealthBar.tga");
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pHealthBarHUD->AddComponent(pMeshRenderer);
		pHealthBarHUD->AddComponent(make_shared<PlayerHealthBarShowScript>(pHealthBarHUD));
		pHealthBarHUD->AddComponent(make_shared<Transform>());
		pHealthBarHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pHealthBarHUD->GetTransform()->SetLocalPosition(Vec3(1.f, -32.5f, -10.f));
		pHealthBarHUD->GetTransform()->SetLocalScale(Vec3(115.f, 8.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_HEALTH_BAR] = pHealthBarHUD;
	}

	// Skill Box HUD
	{
		shared_ptr<SkillBoxHUD> pSkillBoxHUD = make_shared<SkillBoxHUD>();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Cooldown")->Clone();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pSkillBoxHUD->AddComponent(pMeshRenderer);
		pSkillBoxHUD->AddComponent(make_shared<PlayerFirstSkillShowScript>(pSkillBoxHUD));
		pSkillBoxHUD->AddComponent(make_shared<Transform>());
		pSkillBoxHUD->GetTransform()->SetParent(pInterfaceHUD->GetTransform());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pSkillBoxHUD->GetTransform()->SetLocalPosition(Vec3(-63.f, 11.5f, -10.f));
		pSkillBoxHUD->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

		m_mInterfaceMap[INTERFACE_TYPE::PLAYER_SKILL_BOX_FIRST] = pSkillBoxHUD;
	}

}
