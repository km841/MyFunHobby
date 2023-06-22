#include "pch.h"
#include "VeteranHeroDeadObject.h"
#include "Player.h"
#include "Input.h"
#include "Transform.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Engine.h"
#include "ObjectFactory.h"
#include "LocalEffect.h"
#include "HealthPotion.h"

VeteranHeroDeadObject::VeteranHeroDeadObject()
	: GameObject(LAYER_TYPE::DROP_ITEM)
	, m_bIsCollisionWithPlayer(false)
	, m_fCount(0.f)
{
}

VeteranHeroDeadObject::~VeteranHeroDeadObject()
{
}

void VeteranHeroDeadObject::Awake()
{
	GameObject::Awake();
	//CreateHoveringKeyAndAddedToScene();
}

void VeteranHeroDeadObject::Start()
{
	GameObject::Start();
}

void VeteranHeroDeadObject::Update()
{
	GameObject::Update();

	//if (m_bIsCollisionWithPlayer && m_fCount < 6.f)
	//{
	//	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	//	Vec3 vFontPos = vPos;
	//	vFontPos.x += 10.f;
	//	vFontPos.y -= 30.f;
	//	FONT->DrawStringAtWorldPos(L"살펴보기", 20.f, vFontPos, FONT_WEIGHT::BOLD);
	//	// F키 띄우기
	//	m_pHoveringKeyEffect->Enable();
	//	if (IS_DOWN(KEY_TYPE::F))
	//	{
	//		// Health Posion
	//		shared_ptr<HealthPotion> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<HealthPotion>(
	//			L"Forward", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties());

	//		Vec3 vItemPos = vPos;
	//		vItemPos.z -= 1;
	//		pGameObject->GetTransform()->SetLocalPosition(vItemPos);

	//		float fAngle = static_cast<float>(RANDOM(80, 100));
	//		float fRadian = fAngle * XM_PI / 180.f;

	//		PxVec3 vRightNormal = PxVec3(1.f, 0.f, 0.f);
	//		PxVec3 vRotatedNormal = PxVec3(
	//			vRightNormal.x * cosf(fRadian) + vRightNormal.y * sinf(fRadian),
	//			vRightNormal.x * sinf(fRadian) - vRightNormal.y * cosf(fRadian),
	//			0.f
	//		);

	//		int32 iRandomImpulse = RANDOM(400, 1200);
	//		pGameObject->GetRigidBody()->SetLinearVelocityForDynamic(vRotatedNormal * static_cast<float>(iRandomImpulse));

	//		pGameObject->Awake();
	//		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	//		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));
	//	}
	//}
	//else
	//{
	//	m_pHoveringKeyEffect->Disable();
	//}
}

void VeteranHeroDeadObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void VeteranHeroDeadObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void VeteranHeroDeadObject::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
	}
}

void VeteranHeroDeadObject::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void VeteranHeroDeadObject::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void VeteranHeroDeadObject::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}

void VeteranHeroDeadObject::CreateHealthPosionAndAddedToScene()
{
}

void VeteranHeroDeadObject::CreateHoveringKeyAndAddedToScene()
{
	m_pHoveringKeyEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LocalEffect>(
		L"Forward", L"..\\Resources\\Texture\\Key\\Image_Key_F.png");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.x -= 45.f;
	vPos.y -= 80.f;
	vPos.z -= 5.f;

	m_pHoveringKeyEffect->GetTransform()->SetLocalPosition(vPos);
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHoveringKeyEffect, SCENE_TYPE::DUNGEON));
}
