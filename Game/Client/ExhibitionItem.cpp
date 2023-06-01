#include "pch.h"
#include "ExhibitionItem.h"
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

ExhibitionItem::ExhibitionItem(ITEM_KIND eItemKind, int32 iPrice)
	: GameObject(LAYER_TYPE::DROP_ITEM)
	, m_bIsCollisionWithPlayer(false)
	, m_eItemKind(eItemKind)
	, m_iPrice(iPrice)
	, m_bDestroyFlag(false)
{
}

ExhibitionItem::~ExhibitionItem()
{
}

void ExhibitionItem::Awake()
{
	GameObject::Awake();
	CreateDetailHUDAndAddedToScene();
}

void ExhibitionItem::Start()
{
	GameObject::Start();
}

void ExhibitionItem::Update()
{
	GameObject::Update();
	if (m_bIsCollisionWithPlayer)
	{
		weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
		if (IS_DOWN(KEY_TYPE::F) && pPlayer.lock()->GetClobber()->iGold >= m_iPrice)
		{
			m_bDestroyFlag = true;
			pPlayer.lock()->GetClobber()->iGold -= m_iPrice;
			pPlayer.lock()->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem(m_eItemKind));
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
		}

		m_pDetailHUD.lock()->Enable();
	}

	else
	{
		m_pDetailHUD.lock()->Disable();
	}
}

void ExhibitionItem::LateUpdate()
{
	GameObject::LateUpdate();
}

void ExhibitionItem::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void ExhibitionItem::Destroy()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));
}

void ExhibitionItem::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
}

void ExhibitionItem::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void ExhibitionItem::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void ExhibitionItem::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}

void ExhibitionItem::CreateDetailHUDAndAddedToScene()
{
	shared_ptr<GameObject> pDetailHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupItem.png", LAYER_TYPE::UNKNOWN);
	
	Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
	vMyPos.x -= 300.f;
	vMyPos.y += 50.f;
	pDetailHUD->GetTransform()->SetLocalPosition(vMyPos);
	pDetailHUD->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDetailHUD, eSceneType));

	m_pDetailHUD = pDetailHUD;
}
