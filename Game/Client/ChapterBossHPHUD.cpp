#include "pch.h"
#include "ChapterBossHPHUD.h"
#include "Engine.h"
#include "Transform.h"
#include "Clock.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "BossHPScript.h"
#include "EventManager.h"
#include "ObjectRemoveToSceneEvent.h"

ChapterBossHPHUD::ChapterBossHPHUD()
	:m_eStageKind(STAGE_KIND::END)
	, m_bAction(false)
	, m_tDuration(0.5f)
	, m_fSpeed(300.f)
{
}

ChapterBossHPHUD::~ChapterBossHPHUD()
{
}

void ChapterBossHPHUD::Awake()
{
	HUD::Awake();
}

void ChapterBossHPHUD::Start()
{
	HUD::Start();
}

void ChapterBossHPHUD::Update()
{
	HUD::Update();

	if (m_bAction)
	{
		UpdateAction();

		if (!m_pBoss.lock()->GetStatus()->IsAlive())
		{
			if (m_pHPHUD.lock())
			{
				
				m_bAction = false;
			}
		}
	}


}

void ChapterBossHPHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void ChapterBossHPHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void ChapterBossHPHUD::Action()
{
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight, 50.f));
	CreateHPHUDAndAddedToScene();
	assert(m_eStageKind != STAGE_KIND::END);
	m_bAction = true;
	Enable();

}

void ChapterBossHPHUD::Enable()
{
	HUD::Enable();
	if (m_pHPHUD.lock())
		m_pHPHUD.lock()->Enable();
}

void ChapterBossHPHUD::Disable()
{
	if (m_pHPHUD.lock())
		m_pHPHUD.lock()->Disable();
	HUD::Disable();
}

void ChapterBossHPHUD::UpdateAction()
{
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	if (!m_tDuration.IsRunning())
	{
		m_tDuration.Start();
		//GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight, 50.f));
	}

	else
	{
		m_tDuration.Update(WORLD_DELTA_TIME);

		const Vec3& vMyPos = GetTransform()->GetLocalPosition();
		GetTransform()->SetLocalPosition(Vec3(vMyPos.x, vMyPos.y - m_fSpeed * WORLD_DELTA_TIME, vMyPos.z));

		if (m_tDuration.IsFinished())
		{
			m_bAction = false;
			m_tDuration.Reset();
		}
	}
}

void ChapterBossHPHUD::SetStageKind(STAGE_KIND eStageKind)
{
	m_eStageKind = eStageKind;

	switch (eStageKind)
	{
	case STAGE_KIND::BLACK_LAB:
	{
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Ch3BossHP", L"..\\Resources\\Texture\\HUD\\Dungeon\\Ch3\\Image_Ch3_Boss_HPBar.png");
		GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	}
		break;
	case STAGE_KIND::CITADEL_OF_FATE:
		assert(nullptr);
		break;
	}
}



void ChapterBossHPHUD::CreateHPHUDAndAddedToScene()
{
	shared_ptr<HUD> pHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HUD>(L"MonsterHP", L"..\\Resources\\Texture\\HUD\\HealthBar\\BossHealthBar_SecondPhase.png");
	pHUD->AddComponent(make_shared<BossHPScript>(m_pBoss.lock()));
	pHUD->GetTransform()->SetParent(GetTransform());
	pHUD->GetTransform()->SetLocalPosition(Vec3(0.f, 1.f, -0.5f));
	pHUD->GetTransform()->SetLocalScale(Vec3(317.f, 10.f, 1.f));
	
	pHUD->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pHUD, eSceneType));

	m_pHPHUD = pHUD;
}
