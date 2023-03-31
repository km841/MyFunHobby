#include "pch.h"
#include "AfterImage.h"

POOL_INIT(AfterImage);
AfterImage::AfterImage()
	: GameObject(LAYER_TYPE::AFTER_IMAGE)
{
}

AfterImage::~AfterImage()
{
}

void AfterImage::Awake()
{
	GameObject::Awake();
}

void AfterImage::Start()
{
	GameObject::Start();
}

void AfterImage::Update()
{
	GameObject::Update();
}

void AfterImage::LateUpdate()
{
	GameObject::LateUpdate();
}

void AfterImage::FinalUpdate()
{
	GameObject::FinalUpdate();
}

