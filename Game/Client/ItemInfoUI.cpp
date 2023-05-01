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
	// �ڽ��� ��ġ�� �ش��ϴ� �÷��̾��� �����۱׷쿡 �����ؼ� �������� �޾ƿ´�
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

void ItemInfoUI::ShowItemInMyPlace()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	
	weak_ptr<Item> pItem = pPlayer.lock()->GetItem(m_eItemPlace);
	if (!pItem.lock())
		return;

	const ItemInfo& itemInfo = pItem.lock()->GetItemInfo();
	assert(itemInfo.pItemTexture);

	GetMeshRenderer()->GetMaterial()->SetTexture(1, itemInfo.pItemTexture);
}
