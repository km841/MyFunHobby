#include "pch.h"
#include "BoneReward.h"
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

BoneReward::BoneReward(GRADE eGrade)
	: MapReward(eGrade)
{
}

BoneReward::~BoneReward()
{
}

void BoneReward::Awake()
{
	MapReward::Awake();
	CreateHoveringKeyAndAddedToScene();
}

void BoneReward::Start()
{
	MapReward::Start();
}

void BoneReward::Update()
{
	MapReward::Update();
	if (m_bIsCollisionWithPlayer && !m_bTaked)
	{
		Vec3 vFontPos = GetTransform()->GetPhysicalPosition();
		vFontPos.x += 10.f;
		switch (m_eGrade)
		{
		case GRADE::NORMAL:
		case GRADE::RARE:
			vFontPos.y -= 60.f;
			break;
		case GRADE::UNIQUE:
			vFontPos.y -= 120.f;
			break;
		case GRADE::LEGENDARY:
			vFontPos.y -= 150.f;
			break;
		}

		FONT->DrawStringAtWorldPos(L"살펴보기", 20.f, vFontPos, FONT_WEIGHT::BOLD);
		// F키 띄우기
		m_pHoveringKeyEffect->Enable();
		if (IS_DOWN(KEY_TYPE::F))
		{
			// Active Open Animation! 
			GetAnimator()->Play(L"Deactivate_Bone", false);

			// Item Drop!
			m_bTaked = true;
		}
	}
	else
	{
		m_pHoveringKeyEffect->Disable();
	}
}

void BoneReward::LateUpdate()
{
	MapReward::LateUpdate();
}

void BoneReward::FinalUpdate()
{
	MapReward::FinalUpdate();
}

void BoneReward::CreateHoveringKeyAndAddedToScene()
{
	m_pHoveringKeyEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LocalEffect>(
		L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_F.png");

	Vec3 vKeyPos = GetTransform()->GetPhysicalPosition();
	vKeyPos.x -= 45.f;
	vKeyPos.z -= 5.f;

	switch (m_eGrade)
	{
	case GRADE::NORMAL:
	case GRADE::RARE:
		vKeyPos.y -= 70.f;
		break;
	case GRADE::UNIQUE:
		vKeyPos.y -= 130.f;
		break;
	case GRADE::LEGENDARY:
		vKeyPos.y -= 160.f;
		break;
	}

	m_pHoveringKeyEffect->GetTransform()->SetLocalPosition(vKeyPos);
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHoveringKeyEffect, SCENE_TYPE::DUNGEON));
}
