#include "pch.h"
#include "Possession.h"

Possession::Possession()
	: GameObject(LAYER_TYPE::POSSESSION)
{
}

Possession::~Possession()
{
}

void Possession::Awake()
{
	GameObject::Awake();
}

void Possession::Start()
{
	GameObject::Start();
}

void Possession::Update()
{
	GameObject::Update();
}

void Possession::LateUpdate()
{
	GameObject::LateUpdate();
}

void Possession::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Possession::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void Possession::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
