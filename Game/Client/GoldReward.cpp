#include "pch.h"
#include "GoldReward.h"
#include "LocalEffect.h"
#include "Engine.h"
#include "Transform.h"
#include "Input.h"
#include "ObjectFactory.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "DropingRewards.h"
#include "Animator.h"

GoldReward::GoldReward()
	: MapReward(GRADE::NORMAL)
{
}

GoldReward::~GoldReward()
{
}

void GoldReward::Awake()
{
	MapReward::Awake();
	CreateHoveringKeyAndAddedToScene();
}

void GoldReward::Start()
{
	MapReward::Start();
}

void GoldReward::Update()
{
	MapReward::Update();

	if (m_bIsCollisionWithPlayer && !m_bTaked)
	{
		Vec3 vPos = GetTransform()->GetPhysicalPosition();
		Vec3 vFontPos = vPos;
		vFontPos.x += 10.f;
		vFontPos.y -= 100.f;
		FONT->DrawStringAtWorldPos(L"살펴보기", 20.f, vFontPos, FONT_WEIGHT::BOLD);
		// F키 띄우기
		m_pHoveringKeyEffect->Enable();
		if (IS_DOWN(KEY_TYPE::F))
		{
			ScatterGold();
			// Item Drop!
			m_bTaked = true;
			Disable();
		}
	}
	else
	{
		m_pHoveringKeyEffect->Disable();
	}
}

void GoldReward::LateUpdate()
{
	MapReward::LateUpdate();
}

void GoldReward::FinalUpdate()
{
	MapReward::FinalUpdate();
}

void GoldReward::ScatterGold()
{

	for (int32 i = 0; i < 20; ++i)
	{
		shared_ptr<DropingRewards> pGold = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<DropingRewards>(
			L"Forward", false,
			ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(10.f, 10.f, 10.f), MassProperties(10.f, 10.f, 1.f), L"", static_cast<int32>(DROPING_REWARD_KIND::GOLD));

		pGold->AddComponent(make_shared<Animator>());

		// Gold Spin
		{
			shared_ptr<Animation> pSpinAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Gold_Spin", L"..\\Resources\\Animation\\MonsterCommon\\gold_spin.anim");
			pGold->GetAnimator()->AddAnimation(L"Gold_Spin", pSpinAnimation);
		}

		// Gold Get
		{
			shared_ptr<Animation> pGetAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rewards_Get", L"..\\Resources\\Animation\\MonsterCommon\\gold_get.anim");
			pGold->GetAnimator()->AddAnimation(L"Rewards_Get", pGetAnimation);
		}

		pGold->GetAnimator()->Play(L"Gold_Spin");

		Vec3 vMyPos = GetTransform()->GetWorldPosition();
		vMyPos.z = 90.f;
		pGold->GetTransform()->SetLocalPosition(vMyPos);

		Vec3 vRightNormal = VEC3_RIGHT_NORMAL;

		int32 iRandomDegree = RANDOM(60, 120);
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomForce = RANDOM(600, 800);

		int32 iRandomAngularVelocity = RANDOM(-30, 30);
		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pGold->Awake();
		pGold->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, static_cast<float>(iRandomAngularVelocity)));
		pGold->GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(Conv::Vec3ToPxVec3(vRotatedVec * static_cast<float>(iRandomForce)));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGold, eSceneType));
	}
}

void GoldReward::CreateHoveringKeyAndAddedToScene()
{
	m_pHoveringKeyEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LocalEffect>(
		L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_F.png");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.x -= 45.f;
	vPos.y -= 110.f;
	vPos.z -= 5.f;

	m_pHoveringKeyEffect->GetTransform()->SetLocalPosition(vPos);
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHoveringKeyEffect, SCENE_TYPE::DUNGEON));
}
