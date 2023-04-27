#include "pch.h"
#include "DetailInfoUI.h"
#include "InfoUI.h"

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

	if (m_DetailInfo.bUse)
	{
		switch (m_DetailInfo.eInfoType)
		{
		case INFO_TYPE::SKUL_INFO:
		{
			int a = 0;
		}
			break;

		case INFO_TYPE::ITEM_INFO:
			break;

		case INFO_TYPE::ARTIFACT_INFO:
			break;

		case INFO_TYPE::DARKABIL_INFO:
			break;
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
