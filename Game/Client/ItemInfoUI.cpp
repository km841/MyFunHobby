#include "pch.h"
#include "ItemInfoUI.h"
#include "Player.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "Scene.h"
#include "Scenes.h"
#include "Item.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Engrave.h"

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
	// 자신의 위치에 해당하는 플레이어의 아이템그룹에 접근해서 아이템을 받아온다
	ShowItemInMyPlace();
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
	weak_ptr<Item> pItem = pPlayer.lock()->GetItem(m_eItemPlace);
	if (!pItem.lock())
		return;

	const ItemInfo& itemInfo = pItem.lock()->GetItemInfo();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;

	m_DetailInfo.itemInfo = itemInfo;
	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}

ENGRAVES ItemInfoUI::GetEngravesInMyPlace()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	weak_ptr<Item> pItem = pPlayer.lock()->GetItem(m_eItemPlace);
	if (!pItem.lock())
		return std::pair(ENGRAVE::END, ENGRAVE::END);

	return ENGRAVES(pItem.lock()->GetItemInfo().pFirstEngrave->GetEngrave(), 
					pItem.lock()->GetItemInfo().pSecondEngrave->GetEngrave());
}

void ItemInfoUI::ShowItemInMyPlace()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	
	weak_ptr<Item> pItem = pPlayer.lock()->GetItem(m_eItemPlace);
	if (!pItem.lock())
	{
		m_bUnused = true;
		return;
	}
	else
	{
		m_bUnused = false;
	}

	const ItemInfo& itemInfo = pItem.lock()->GetItemInfo();
	assert(itemInfo.pItemTexture);

	GetMeshRenderer()->GetMaterial()->SetTexture(1, itemInfo.pItemTexture);
}
