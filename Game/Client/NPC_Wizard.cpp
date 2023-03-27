#include "pch.h"
#include "NPC_Wizard.h"

NPC_Wizard::NPC_Wizard()
	: GameObject(LAYER_TYPE::NPC)
{
}

NPC_Wizard::~NPC_Wizard()
{
}

void NPC_Wizard::Awake()
{
	GameObject::Awake();
}

void NPC_Wizard::Start()
{
	GameObject::Start();
}

void NPC_Wizard::Update()
{
	GameObject::Update();
}

void NPC_Wizard::LateUpdate()
{
	GameObject::LateUpdate();
}

void NPC_Wizard::FinalUpdate()
{
	GameObject::FinalUpdate();
}
