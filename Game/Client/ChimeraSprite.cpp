#include "pch.h"
#include "ChimeraSprite.h"

ChimeraSprite::ChimeraSprite()
	: GameObject(LAYER_TYPE::UNKNOWN)
{
}

ChimeraSprite::~ChimeraSprite()
{
}

void ChimeraSprite::Awake()
{
	GameObject::Awake();
}

void ChimeraSprite::Start()
{
	GameObject::Start();
}

void ChimeraSprite::Update()
{
	GameObject::Update();
}

void ChimeraSprite::LateUpdate()
{
	GameObject::LateUpdate();
}

void ChimeraSprite::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void ChimeraSprite::Destroy()
{
}
