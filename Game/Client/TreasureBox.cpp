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

			// Temp Code
			wstring szPathList[] = {
				L"..\\Resources\\Texture\\Item\\ForbiddenSword\\Image_ForbiddenSword.png",
				L"..\\Resources\\Texture\\Item\\EvilSwordKirion\\Image_EvilSwordKirion.png"
			};
			// Temp Code
			ITEM_KIND eItemKind[] = {
				ITEM_KIND::FORBIDDEN_SWORD,
				ITEM_KIND::EVIL_SWORD_KIRION,
			};

			// Temp Code
			for (uint8 i = 0; i < 2; ++i)
			{
				shared_ptr<DropItem> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DropItem>(
					L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties(), szPathList[i], eItemKind[i], i ? DROP_ITEM_INDEX::FIRST : DROP_ITEM_INDEX::SECOND);
				Vec3 vItemPos = vPos;
				vItemPos.z -= 1;
				pGameObject->GetTransform()->SetLocalPosition(vItemPos);

				float fAngle = i ? 75.f : 105.f;
				float fRadian = fAngle * XM_PI / 180.f;

				PxVec3 vRightNormal = PxVec3(1.f, 0.f, 0.f);
				PxVec3 vRotatedNormal = PxVec3(
					vRightNormal.x * cosf(fRadian) + vRightNormal.y * sinf(fRadian),
					vRightNormal.x * sinf(fRadian) - vRightNormal.y * cosf(fRadian),
					0.f
				);

				pGameObject->GetRigidBody()->SetLinearVelocityForDynamic(vRotatedNormal * 500.f);

				pGameObject->Awake();
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));
			}

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
