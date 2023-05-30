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
#include "DropSkul.h"

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

			shared_ptr<DropSkul> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DropSkul>(
				L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties(), L"..\\Resources\\Texture\\HUD\\HighWarlock\\Image_HighWarlock_Drop.png", SKUL_KIND::HIGH_WARLOCK);
			Vec3 vSkulPos = GetTransform()->GetPhysicalPosition();
			vSkulPos.z -= 1;
			pGameObject->GetTransform()->SetLocalPosition(vSkulPos);

			PxVec3 vUpNormal = PxVec3(0.f, 1.f, 0.f);
			pGameObject->GetRigidBody()->SetLinearVelocityForDynamic(vUpNormal * 500.f);

			pGameObject->Awake();
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));

			// Skul Drop!
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
