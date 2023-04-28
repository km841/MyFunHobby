#include "pch.h"
#include "DarkAbilInfoUI.h"
#include "Player.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "Scene.h"
#include "Scenes.h"

DarkAbilInfoUI::DarkAbilInfoUI()
	: InfoUI(INFO_TYPE::DARKABIL_INFO)
{
}

DarkAbilInfoUI::~DarkAbilInfoUI()
{
}

void DarkAbilInfoUI::Awake()
{
	InfoUI::Awake();
}

void DarkAbilInfoUI::Start()
{
	InfoUI::Start();
}

void DarkAbilInfoUI::Update()
{
	InfoUI::Update();
}

void DarkAbilInfoUI::LateUpdate()
{
	InfoUI::LateUpdate();
}

void DarkAbilInfoUI::FinalUpdate()
{
	InfoUI::FinalUpdate();
}

void DarkAbilInfoUI::ShowDetailInfo()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;

	m_DetailInfo.szComment = L"";
	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}
