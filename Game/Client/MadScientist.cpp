#include "pch.h"
#include "MadScientist.h"

MadScientist::MadScientist()
	: GameObject(LAYER_TYPE::NPC)
{
}

MadScientist::~MadScientist()
{
}

void MadScientist::Awake()
{
	GameObject::Awake();
}

void MadScientist::Start()
{
	GameObject::Start();
}

void MadScientist::Update()
{
	GameObject::Update();
}

void MadScientist::LateUpdate()
{
	GameObject::LateUpdate();
}

void MadScientist::FinalUpdate()
{
	GameObject::FinalUpdate();
}
