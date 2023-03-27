#include "pch.h"
#include "NPC_Wolf.h"

NPC_Wolf::NPC_Wolf()
	: GameObject(LAYER_TYPE::NPC)
{
}

NPC_Wolf::~NPC_Wolf()
{
}

void NPC_Wolf::Awake()
{
	GameObject::Awake();
}

void NPC_Wolf::Start()
{
	GameObject::Start();
}

void NPC_Wolf::Update()
{
	GameObject::Update();
}

void NPC_Wolf::LateUpdate()
{
	GameObject::LateUpdate();
}

void NPC_Wolf::FinalUpdate()
{
	GameObject::FinalUpdate();
}
