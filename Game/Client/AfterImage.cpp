#include "pch.h"
#include "AfterImage.h"

AfterImage::AfterImage(AFTERIMAGE_TYPE eAfterImageType)
	: GameObject(LAYER_TYPE::AFTER_IMAGE)
	, m_eAfterImageType(eAfterImageType)
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

