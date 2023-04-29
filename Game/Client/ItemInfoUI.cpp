#include "pch.h"
#include "ItemInfoUI.h"
#include "Player.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "Scene.h"
#include "Scenes.h"

ItemInfoUI::ItemInfoUI(ITEM_PLACE eItemPlace)
	: InfoUI(INFO_TYPE::ITEM_INFO)
	, m_eItemPlace(eItemPlace)
{
}

ItemInfoUI::~ItemInfoUI()
{
}

void ItemInfoUI::Awake()
{
	InfoUI::Awake();
}

void ItemInfoUI::Start()
{
	InfoUI::Start();
}

void ItemInfoUI::Update()
{
	InfoUI::Update();
}

void ItemInfoUI::LateUpdate()
{
	InfoUI::LateUpdate();
}

void ItemInfoUI::FinalUpdate()
{
	InfoUI::FinalUpdate();
}

void ItemInfoUI::ShowDetailInfo()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;

	m_DetailInfo.szComment = L"";
	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}
