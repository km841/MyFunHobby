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
		if (IS_DOWN(KEY_TYPE::F))
		{
			weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
			GET_SINGLE(Cemetery)->Get(m_eSkulKind)->Awake();
			pPlayer.lock()->ObtainSkul(GET_SINGLE(Cemetery)->Get(m_eSkulKind));

			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));

			GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::DROP_SKUL)->Action();
		}

		if (m_bFixed)
		{
			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			vMyPos = GET_SINGLE(Scenes)->WorldToScreenPosition(vMyPos, GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera());
			vMyPos.y += 50.f;

			GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_SKUL)->GetTransform()->SetLocalPosition(vMyPos);
			GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_SKUL)->Enable();
		}

	}
	else
	{
		GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::DROP_SKUL)->Disable();
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
