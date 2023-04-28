#include "pch.h"
#include "DetailInfoUI.h"
#include "InfoUI.h"
#include "Font.h"
#include "InventoryUI.h"

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
	//GET_SINGLE(Font)->DrawString(L"SkulInfo", 20.f, Vec3(16.f, 16.f, 0.f));

	GET_SINGLE(Font)->DrawString(m_DetailInfo.szName, 20.f, Vec3(750.f, 220.f, 0.f), FONT_WEIGHT::LIGHT, Color::FromRGB(136, 96, 90));
	
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
