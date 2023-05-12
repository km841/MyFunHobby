#include "pch.h"
#include "EssenceInfoUI.h"
#include "Player.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "Scene.h"
#include "Scenes.h"
#include "Essence.h"
#include "MeshRenderer.h"
#include "Material.h"

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
	ShowEssenceInMyPlace();
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
	weak_ptr<Essence> pEssence = pPlayer.lock()->GetEssence();

	if (!pEssence.lock())
		return;

	const EssenceInfo& essenceInfo = pEssence.lock()->GetEssenceInfo();
	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;
	m_DetailInfo.essenceInfo = essenceInfo;

	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}

void EssenceInfoUI::ShowEssenceInMyPlace()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	weak_ptr<Essence> pEssence = pPlayer.lock()->GetEssence();

	if (!pEssence.lock())
	{
		m_bUnused = true;
		GetMeshRenderer()->GetMaterial()->SetTexture(1, nullptr);
		return;
	}
	else
	{
		m_bUnused = false;
	}

	const EssenceInfo& essenceInfo = pEssence.lock()->GetEssenceInfo();
	GetMeshRenderer()->GetMaterial()->SetTexture(1, essenceInfo.pEssenceTexture);
}
