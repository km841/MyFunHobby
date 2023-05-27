#include "pch.h"
#include "DropSkul.h"

DropSkul::DropSkul(SKUL_KIND eSkulKind)
	: GameObject(LAYER_TYPE::DROP_SKUL)
	, m_eSkulKind(eSkulKind)
	, m_bIsCollisionWithPlayer(false)
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
