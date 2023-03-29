#include "pch.h"
#include "UIManager.h"

#include "DialogueUI.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Transform.h"

#include "Resources.h"

void UIManager::Init()
{
	CreateUI();
}

shared_ptr<UI> UIManager::Get(UI_TYPE eUIType)
{
	auto iter = m_mUIMap.find(eUIType);
	assert(iter != m_mUIMap.end());
	return iter->second;
}

void UIManager::CreateUI()
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

		pDialogueUI->GetTransform()->SetLocalScale(pTexture->GetTexSize());

		m_mUIMap[UI_TYPE::DIALOGUE] = pDialogueUI;
	}
	
}
