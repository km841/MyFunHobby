#include "pch.h"
#include "ViceBossHPHUD.h"
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

ViceBossHPHUD::ViceBossHPHUD()
	: m_bAction(false)
	, m_tDuration(0.5f)
	, m_fSpeed(300.f)
{
}

ViceBossHPHUD::~ViceBossHPHUD()
{
}

void ViceBossHPHUD::Awake()
{
	HUD::Awake();
}

void ViceBossHPHUD::Start()
{
	HUD::Start();
}

void ViceBossHPHUD::Update()
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

void ViceBossHPHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void ViceBossHPHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void ViceBossHPHUD::Destroy()
{
	if (m_pHPHUD.lock())
	{
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pHPHUD.lock(), eSceneType));
		m_pHPHUD.reset();
	}
}

void ViceBossHPHUD::Action()
{
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight, 50.f));
	CreateHPHUDAndAddedToScene();
	m_bAction = true;
	Enable();

}

void ViceBossHPHUD::Enable()
{
	HUD::Enable();
	if (m_pHPHUD.lock())
		m_pHPHUD.lock()->Enable();
}

void ViceBossHPHUD::Disable()
{
	if (m_pHPHUD.lock())
		m_pHPHUD.lock()->Disable();
	HUD::Disable();
}

void ViceBossHPHUD::UpdateAction()
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

void ViceBossHPHUD::CreateHPHUDAndAddedToScene()
{
	shared_ptr<HUD> pHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<HUD>(L"MonsterHP", L"..\\Resources\\Texture\\HUD\\HealthBar\\ViceBoss_HealthBar.png");
	pHUD->AddComponent(make_shared<BossHPScript>(m_pBoss.lock()));
	pHUD->GetTransform()->SetParent(GetTransform());
	pHUD->GetTransform()->SetLocalPosition(Vec3(0.f, 1.f, -0.5f));
	pHUD->GetTransform()->SetLocalScale(Vec3(317.f, 10.f, 1.f));

	pHUD->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pHUD, eSceneType));

	m_pHPHUD = pHUD;
}
