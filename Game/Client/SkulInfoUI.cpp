#include "pch.h"
#include "SkulInfoUI.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Player.h"
#include "Scenes.h"
#include "Scene.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "SkulSkill.h"


SkulInfoUI::SkulInfoUI()
	: InfoUI(INFO_TYPE::SKUL_INFO)
	, m_eSkulIndex(SKUL_INDEX::END)
{
}

SkulInfoUI::~SkulInfoUI()
{
}

void SkulInfoUI::Awake()
{
	InfoUI::Awake();
}

void SkulInfoUI::Start()
{
	InfoUI::Start();
}

void SkulInfoUI::Update()
{
	InfoUI::Update();

	// 자신의 Index에 맞는 스컬 이미지 가져오기
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	weak_ptr<Skul> pSkul = pPlayer.lock()->GetSkul(m_eSkulIndex).lock();
	if (pSkul.lock())
	{
		GetMeshRenderer()->GetMaterial()->SetTexture(1, pSkul.lock()->GetThumnailImage().lock());
	}
}

void SkulInfoUI::LateUpdate()
{
	InfoUI::LateUpdate();
}

void SkulInfoUI::FinalUpdate()
{
	InfoUI::FinalUpdate();
}

void SkulInfoUI::ShowDetailInfo()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	weak_ptr<Skul> pSkul = pPlayer.lock()->GetSkul(m_eSkulIndex).lock();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;
	m_DetailInfo.eGrade = pSkul.lock()->GetSkulGrade();

	if (pSkul.lock()->GetSkill(SKILL_INDEX::FIRST).lock())
		m_DetailInfo.pSkulSkillSecond = pSkul.lock()->GetSkill(SKILL_INDEX::FIRST).lock()->GetTexture().lock();
	if (pSkul.lock()->GetSkill(SKILL_INDEX::SECOND).lock())
		m_DetailInfo.pSkulSkillSecond = pSkul.lock()->GetSkill(SKILL_INDEX::SECOND).lock()->GetTexture().lock();

	m_DetailInfo.pThumnail = pSkul.lock()->GetThumnailImage().lock();

	switch (pSkul.lock()->GetSkulType())
	{
	case SKUL_TYPE::LITTLE_BONE:
		m_DetailInfo.szName = L"리틀 본";
		break;
	case SKUL_TYPE::HIGH_WARLOCK:
		m_DetailInfo.szName = L"대마도사";
		break;
	}
	m_DetailInfo.szComment = L"";

	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}
