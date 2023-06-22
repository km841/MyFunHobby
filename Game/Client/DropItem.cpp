#include "pch.h"
#include "DropItem.h"
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
#include "Engine.h"
#include "Engrave.h"

DropItem::DropItem(ITEM_KIND eItemKind, DROP_ITEM_INDEX eItemIndex)
	: GameObject(LAYER_TYPE::DROP_ITEM)
	, m_eItemKind(eItemKind)
	, m_bIsCollisionWithPlayer(false)
	, m_bFixed(false)
	, m_eItemIndex(eItemIndex)
{
}

DropItem::~DropItem()
{
}

void DropItem::Awake()
{
	GameObject::Awake();
	CreateDetailHUDAndAddedToScene();
}

void DropItem::Start()
{
	GameObject::Start();
}

void DropItem::Update()
{
	GameObject::Update();

	if (m_bIsCollisionWithPlayer)
	{
		weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
		if (IS_DOWN(KEY_TYPE::F))
		{
			pPlayer.lock()->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem(m_eItemKind));
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

void DropItem::LateUpdate()
{
	GameObject::LateUpdate();
}

void DropItem::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DropItem::Destroy()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	if (m_pDetailHUD.lock())
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));

	if (m_pVignetteHUD.lock())
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pVignetteHUD.lock(), eSceneType));
}

void DropItem::CreateTouchEffectAddedToScene()
{
}

void DropItem::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		m_bFixed = true;
	}
}

void DropItem::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void DropItem::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void DropItem::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}

void DropItem::CreateDetailHUDAndAddedToScene()
{
	shared_ptr<GameObject> pDetailHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupItem_Ver2.png", LAYER_TYPE::UNKNOWN);
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

void DropItem::DrawItemDetail()
{
	const ItemInfo& itemInfo = GET_SINGLE(ObjectFactory)->GetItemInfo(m_eItemKind);

	Vec3 vStandard = m_pDetailHUD.lock()->GetTransform()->GetWorldPosition();

	// Name
	{
		Vec3 vNamePos = vStandard;
		vNamePos.y += 87.5f;
		FONT->DrawStringAtWorldPos(itemInfo.szName, 23.f, vNamePos, FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR, FONT_ALIGN::CENTER);
	}

	// Grade
	{
		Vec3 vGradePos = vStandard;
		vGradePos.x -= 180.f;
		vGradePos.y += 50.f;
		wstring szGrade = {};
		switch (itemInfo.eGrade)
		{
		case GRADE::NORMAL:
			szGrade = L"노멀";
			break;
		case GRADE::RARE:
			szGrade = L"레어";
			break;
		case GRADE::UNIQUE:
			szGrade = L"유니크";
			break;
		case GRADE::LEGENDARY:
			szGrade = L"레전더리";
			break;
		}
		FONT->DrawStringAtWorldPos(szGrade, 17.f, vGradePos, FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR, FONT_ALIGN::CENTER);
	}

	// Comment
	{
		Vec3 vCommentPos = vStandard;
		vCommentPos.y += 20.f;
		FONT->DrawStringAtWorldPos(itemInfo.szExplanation, 17.f, vCommentPos, FONT_WEIGHT::BOLD, COMMENT_COLOR, FONT_ALIGN::CENTER);
	}
}
