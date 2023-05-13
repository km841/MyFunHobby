#include "pch.h"
#include "TreasureBox.h"
#include "Engine.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "ComponentObject.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "LocalEffect.h"
#include "Animator.h"

TreasureBox::TreasureBox(GRADE eGrade)
	: MapReward(eGrade)
{
}

TreasureBox::~TreasureBox()
{
}

void TreasureBox::Awake()
{
	MapReward::Awake();
	CreateHoveringKeyAndAddedToScene();
}

void TreasureBox::Start()
{
	MapReward::Start();
}

void TreasureBox::Update()
{
	MapReward::Update();

	if (m_bIsCollisionWithPlayer && !m_bTaked)
	{
		Vec3 vPos = GetTransform()->GetPhysicalPosition();
		vPos.x += 10.f;
		vPos.y -= 60.f;
		FONT->DrawStringAtWorldPos(L"살펴보기", 20.f, vPos, FONT_WEIGHT::BOLD);
		// F키 띄우기
		m_pHoveringKeyEffect->Enable();
		if (IS_DOWN(KEY_TYPE::F))
		{
			// Active Open Animation! 
			GetAnimator()->Play(L"TreasureBox_Open", false);

			// Item Drop!
			m_bTaked = true;
		}
	}
	else
	{
		m_pHoveringKeyEffect->Disable();
	}

}

void TreasureBox::LateUpdate()
{
	MapReward::LateUpdate();
}

void TreasureBox::FinalUpdate()
{
	MapReward::FinalUpdate();
}

void TreasureBox::CreateHoveringKeyAndAddedToScene()
{
	m_pHoveringKeyEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LocalEffect>(
		L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_F.png");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.x -= 45.f;
	vPos.y -= 70.f;
	vPos.z -= 5.f;

	m_pHoveringKeyEffect->GetTransform()->SetLocalPosition(vPos);
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHoveringKeyEffect, SCENE_TYPE::DUNGEON));
}
