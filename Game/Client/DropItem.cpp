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

DropItem::DropItem(ITEM_KIND eItemKind)
	: GameObject(LAYER_TYPE::DROP_ITEM)
	, m_eItemKind(eItemKind)
	, m_bIsCollisionWithPlayer(false)
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

	Vec3 vMyPos = GetTransform()->GetPhysicalPosition();

	static float fWaveValue = 0.f;
	static float fAcc = 0.f;
	fAcc += DELTA_TIME;
	fWaveValue = sinf(fAcc) * 0.05f;
	GetTransform()->SetPhysicalPosition(Vec3(vMyPos.x, vMyPos.y + fWaveValue, vMyPos.z));

	if (m_bIsCollisionWithPlayer && IS_DOWN(KEY_TYPE::F))
	{
		weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
		pPlayer.lock()->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem(m_eItemKind));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
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
