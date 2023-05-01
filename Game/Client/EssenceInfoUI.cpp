#include "pch.h"
#include "EssenceInfoUI.h"
#include "Player.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "Scene.h"
#include "Scenes.h"

EssenceInfoUI::EssenceInfoUI()
	:InfoUI(INFO_TYPE::ESSENCE_INFO)
{
}

EssenceInfoUI::~EssenceInfoUI()
{
}

void EssenceInfoUI::Awake()
{
	InfoUI::Awake();
}

void EssenceInfoUI::Start()
{
	InfoUI::Start();
}

void EssenceInfoUI::Update()
{
	InfoUI::Update();
}

void EssenceInfoUI::LateUpdate()
{
	InfoUI::LateUpdate();
}

void EssenceInfoUI::FinalUpdate()
{
	InfoUI::FinalUpdate();
}

void EssenceInfoUI::ShowDetailInfo()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;

	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}
