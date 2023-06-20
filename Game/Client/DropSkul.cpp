#include "pch.h"
#include "DropSkul.h"
#include "Transform.h"
#include "Clock.h"
#include "Input.h"
#include "Player.h"
#include "Scenes.h"
#include "Item.h"
#include "ObjectFactory.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "InterfaceManager.h"
#include "Interface.h"
#include "ComponentObject.h"
#include "HUD.h"
#include "Cemetery.h"
#include "Skul.h"
#include "Engine.h"


DropSkul::DropSkul(SKUL_KIND eSkulKind)
	: GameObject(LAYER_TYPE::DROP_SKUL)
	, m_eSkulKind(eSkulKind)
	, m_bIsCollisionWithPlayer(false)
	, m_bFixed(false)
{
}

DropSkul::~DropSkul()
{
}

void DropSkul::Awake()
{
	GameObject::Awake();
	CreateDetailHUDAndAddedToScene();
}

void DropSkul::Start()
{
	GameObject::Start();
}

void DropSkul::Update()
{
	GameObject::Update();

	if (m_bIsCollisionWithPlayer)
	{
		weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
		if (IS_DOWN(KEY_TYPE::F))
		{
			GET_SINGLE(Cemetery)->Get(m_eSkulKind)->Awake();
			pPlayer.lock()->ObtainSkul(GET_SINGLE(Cemetery)->Get(m_eSkulKind));
			pPlayer.lock()->EnableSwapActiveFlag();
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pVignetteHUD.lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
		}

		m_pDetailHUD.lock()->Enable();
		m_pVignetteHUD.lock()->Enable();
		DrawItemDetail();
	}

	else
	{
		m_pDetailHUD.lock()->Disable();
		m_pVignetteHUD.lock()->Disable();
	}
}

void DropSkul::LateUpdate()
{
	GameObject::LateUpdate();
}

void DropSkul::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DropSkul::Destroy()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	if (m_pDetailHUD.lock())
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));

	if (m_pVignetteHUD.lock())
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pVignetteHUD.lock(), eSceneType));
}

void DropSkul::CreateTouchEffectAddedToScene()
{
}

void DropSkul::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		m_bFixed = true;
	}
}

void DropSkul::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void DropSkul::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}

void DropSkul::DrawItemDetail()
{
	Vec3 vStandard = m_pDetailHUD.lock()->GetTransform()->GetWorldPosition();

	// Name
	{
		Vec3 vNamePos = vStandard;
		vNamePos.y += 137.5f;
		FONT->DrawStringAtWorldPos(L"대마도사", 23.f, vNamePos, FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR, FONT_ALIGN::CENTER);
	}

	// Grade
	{
		Vec3 vGradePos = vStandard;
		vGradePos.x -= 180.f;
		vGradePos.y += 100.f;
		FONT->DrawStringAtWorldPos(L"유니크", 17.f, vGradePos, FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR, FONT_ALIGN::CENTER);
	}

	// Comment
	{
		Vec3 vCommentPos = vStandard;
		vCommentPos.y += 70.f;
		FONT->DrawStringAtWorldPos(L"마나의 흐름을 느끼는데 살가죽은 방해가 될 뿐이다.\n- 마왕성 제 1 마도 군단장", 17.f, vCommentPos, FONT_WEIGHT::BOLD, COMMENT_COLOR, FONT_ALIGN::CENTER);
	}
}

void DropSkul::CreateDetailHUDAndAddedToScene()
{
	shared_ptr<GameObject> pDetailHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupItem.png", LAYER_TYPE::UNKNOWN);
	pDetailHUD->GetTransform()->SetParent(GetTransform());
	pDetailHUD->GetTransform()->SetLocalPosition(Vec3(0.f, 200.f, 0.f));
	pDetailHUD->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDetailHUD, eSceneType));
	m_pDetailHUD = pDetailHUD;

	shared_ptr<GameObject> pVignetteHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"", LAYER_TYPE::UNKNOWN);
	pVignetteHUD->GetTransform()->SetParent(pDetailHUD->GetTransform());
	pVignetteHUD->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pVignetteHUD, eSceneType));
	m_pVignetteHUD = pVignetteHUD;
}