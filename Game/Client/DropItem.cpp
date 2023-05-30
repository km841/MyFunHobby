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
		if (IS_DOWN(KEY_TYPE::F))
		{
			weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
			pPlayer.lock()->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem(m_eItemKind));

			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));

			GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::DROP_ITEM_FIRST)->Action();
			GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::DROP_ITEM_SECOND)->Action();
		}

		if (m_bFixed)
		{
			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			vMyPos = GET_SINGLE(Scenes)->WorldToScreenPosition(vMyPos, GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera());
			vMyPos.y += 50.f;

			switch (m_eItemIndex)
			{
			case DROP_ITEM_INDEX::FIRST:
				GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_ITEM_FIRST)->GetTransform()->SetLocalPosition(vMyPos);
				GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_ITEM_FIRST)->Enable();
				break
					;
			case DROP_ITEM_INDEX::SECOND:
				GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_ITEM_SECOND)->GetTransform()->SetLocalPosition(vMyPos);
				GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_ITEM_SECOND)->Enable();
				break;
			}
		}

	}
	else
	{
		switch (m_eItemIndex)
		{
		case DROP_ITEM_INDEX::FIRST:
			GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_ITEM_FIRST)->Disable();
			break
				;
		case DROP_ITEM_INDEX::SECOND:
			GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_ITEM_SECOND)->Disable();
			break;
		}
		
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
