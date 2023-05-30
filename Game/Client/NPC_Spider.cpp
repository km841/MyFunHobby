#include "pch.h"
#include "NPC_Spider.h"

NPC_Spider::NPC_Spider()
	: GameObject(LAYER_TYPE::NPC)
{
}

NPC_Spider::~NPC_Spider()
{
}

void NPC_Spider::Awake()
{
	GameObject::Awake();
}

void NPC_Spider::Start()
{
	GameObject::Start();
}

void NPC_Spider::Update()
{
	GameObject::Update();
}

void NPC_Spider::LateUpdate()
{
	GameObject::LateUpdate();
}

void NPC_Spider::FinalUpdate()
{
	GameObject::FinalUpdate();
}
