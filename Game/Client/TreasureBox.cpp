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
#include "DropItem.h"
#include "RigidBody.h"
#include "Player.h"

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
		Vec3 vFontPos = vPos;
		vFontPos.x += 10.f;
		vFontPos.y -= 60.f;
		FONT->DrawStringAtWorldPos(L"살펴보기", 20.f, vFontPos, FONT_WEIGHT::BOLD);
		// F키 띄우기
		m_pHoveringKeyEffect->Enable();
		if (IS_DOWN(KEY_TYPE::F))
		{
			// Active Open Animation! 
			GetAnimator()->Play(L"TreasureBox_Open", false);

			std::vector<ITEM_KIND> vDropItemKinds = {};
			std::vector<ITEM_KIND> vTotalItemKinds = Item::GetItemKindsOfGrade(m_eGrade);
			std::vector<ITEM_KIND> vPlayerItemKinds = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetItemList();
			for (int32 i = 0; i < vTotalItemKinds.size(); ++i)
			{
				if (std::find(vPlayerItemKinds.begin(), vPlayerItemKinds.end(), vTotalItemKinds[i]) == vPlayerItemKinds.end())
					vDropItemKinds.push_back(static_cast<ITEM_KIND>(i));

				if (vDropItemKinds.size() >= 2)
					break;
			}

			for (uint8 i = 0; i < vDropItemKinds.size(); ++i)
			{
				shared_ptr<DropItem> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DropItem>(
					L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties(), Item::GetItemKindToDropItemPath(vDropItemKinds[i]), vDropItemKinds[i], i ? DROP_ITEM_INDEX::FIRST : DROP_ITEM_INDEX::SECOND);
				Vec3 vItemPos = vPos;
				vItemPos.z -= 1;
				pGameObject->GetTransform()->SetLocalPosition(vItemPos);

				float fAngle = i ? 85.f : 95.f;
				float fRadian = fAngle * XM_PI / 180.f;

				PxVec3 vRightNormal = PxVec3(1.f, 0.f, 0.f);
				PxVec3 vRotatedNormal = PxVec3(
					vRightNormal.x * cosf(fRadian) + vRightNormal.y * sinf(fRadian),
					vRightNormal.x * sinf(fRadian) - vRightNormal.y * cosf(fRadian),
					0.f
				);

				pGameObject->GetRigidBody()->SetLinearVelocityForDynamic(vRotatedNormal * 800.f);

				pGameObject->Awake();
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));
			}

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
