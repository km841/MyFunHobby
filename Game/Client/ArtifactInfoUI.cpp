#include "pch.h"
#include "ArtifactInfoUI.h"
#include "Player.h"
#include "Skul.h"
#include "DetailInfoUI.h"
#include "Scene.h"
#include "Scenes.h"

ArtifactInfoUI::ArtifactInfoUI()
	:InfoUI(INFO_TYPE::ARTIFACT_INFO)
{
}

ArtifactInfoUI::~ArtifactInfoUI()
{
}

void ArtifactInfoUI::Awake()
{
	InfoUI::Awake();
}

void ArtifactInfoUI::Start()
{
	InfoUI::Start();
}

void ArtifactInfoUI::Update()
{
	InfoUI::Update();
}

void ArtifactInfoUI::LateUpdate()
{
	InfoUI::LateUpdate();
}

void ArtifactInfoUI::FinalUpdate()
{
	InfoUI::FinalUpdate();
}

void ArtifactInfoUI::ShowDetailInfo()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	m_DetailInfo.bUse = true;
	m_DetailInfo.eInfoType = m_eInfoType;

	m_DetailInfo.szComment = L"";
	m_pDetailInfoUI.lock()->SetDetailInfo(m_DetailInfo);
}
