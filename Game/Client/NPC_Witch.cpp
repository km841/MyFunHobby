#include "pch.h"
#include "NPC_Witch.h"

NPC_Witch::NPC_Witch()
	: GameObject(LAYER_TYPE::NPC)
{
}

NPC_Witch::~NPC_Witch()
{
}

void NPC_Witch::Awake()
{
	GameObject::Awake();
}

void NPC_Witch::Start()
{
	GameObject::Start();
}

void NPC_Witch::Update()
{
	GameObject::Update();
}

void NPC_Witch::LateUpdate()
{
	GameObject::LateUpdate();
}

void NPC_Witch::FinalUpdate()
{
	GameObject::FinalUpdate();
}
