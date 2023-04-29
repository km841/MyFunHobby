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

	m_DetailInfo.skulInfo = pSkul.lock()->GetSkulInfo();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;
	m_DetailInfo.eTotalSkills = pSkul.lock()->GetTotalSkills();
	m_DetailInfo.szSkulType = GetSkulTypeWstring(m_DetailInfo.skulInfo.eSkulType);
	m_DetailInfo.szGrade = GetGradeWstring(m_DetailInfo.skulInfo.eSkulGrade);
	m_DetailInfo.szName = GetSkulKindWstring(pSkul.lock()->GetSkulKind());

	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}
