#include "pch.h"
#include "DetailInfoUI.h"
#include "InfoUI.h"
#include "Font.h"
#include "InventoryUI.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "SkulInfoUI.h"
#include "Transform.h"
#include "Texture.h"

DetailInfoUI::DetailInfoUI()
	:m_DetailInfo{}
{
}

DetailInfoUI::~DetailInfoUI()
{
}

void DetailInfoUI::Awake()
{
	UI::Awake();
}

void DetailInfoUI::Start()
{
	UI::Start();
}

void DetailInfoUI::Update()
{
	UI::Update();
	// 타입에 따른 텍스쳐를 출력한다.

	if (m_pInventoryUI.lock()->IsEnable())
	{
		if (m_DetailInfo.bUse)
		{
			switch (m_DetailInfo.eInfoType)
			{
			case INFO_TYPE::SKUL_INFO:
				DrawSkulInfo();
				break;

			case INFO_TYPE::ITEM_INFO:
				DrawItemInfo();
				break;

			case INFO_TYPE::ARTIFACT_INFO:
				DrawArtifactInfo();
				break;

			case INFO_TYPE::DARKABIL_INFO:
				DrawDarkAbilInfo();
				break;
			}
		}
	}


}

void DetailInfoUI::LateUpdate()
{
	UI::LateUpdate();
}

void DetailInfoUI::FinalUpdate()
{
	UI::FinalUpdate();
}

void DetailInfoUI::DrawSkulInfo()
{
	// 전용 Texture로 변경
	SetSkulDetailTexture();

	GET_SINGLE(Font)->DrawString(m_DetailInfo.szGrade, 20.f, Vec3(775.f, 670.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, GRADE_COLOR);
	GET_SINGLE(Font)->DrawString(m_DetailInfo.szSkulType, 20.f, Vec3(1375.f, 670.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, GRADE_COLOR);
	GET_SINGLE(Font)->DrawString(m_DetailInfo.szName, 25.f, Vec3(1076.f, 685.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
	GET_SINGLE(Font)->DrawString(m_DetailInfo.szComment, 20.f, Vec3(1076.f, 550.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, COMMENT_COLOR);
}

void DetailInfoUI::DrawItemInfo()
{
	GET_SINGLE(Font)->DrawString(L"ItemInfo", 20.f, Vec3(16.f, 16.f, 0.f));
}

void DetailInfoUI::DrawArtifactInfo()
{
	GET_SINGLE(Font)->DrawString(L"ArtifactInfo", 20.f, Vec3(16.f, 16.f, 0.f));
}

void DetailInfoUI::DrawDarkAbilInfo()
{
	GET_SINGLE(Font)->DrawString(L"DarkAbilInfo", 20.f, Vec3(16.f, 16.f, 0.f));
}

void DetailInfoUI::SetSkulDetailTexture()
{
	shared_ptr<Texture> pTexture = nullptr;

	switch (m_DetailInfo.eTotalSkills)
	{
	case SKILL_INDEX::FIRST:
		pTexture = GET_SINGLE(Resources)->Load<Texture>(L"SkulInfoDetail", L"..\\Resources\\Texture\\UI\\Inventory\\Image_Skill01_Frame.png");
		break;
	case SKILL_INDEX::SECOND:
		pTexture = GET_SINGLE(Resources)->Load<Texture>(L"SkulInfoDetail", L"..\\Resources\\Texture\\UI\\Inventory\\Image_Skill02_Frame.png");
		break;
	}

	assert(pTexture);
	GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	GetTransform()->SetLocalScale(pTexture->GetTexSize());
}
