#include "pch.h"
#include "ShopScene.h"
#include "Engine.h"

ShopScene::ShopScene()
	: Scene(SCENE_TYPE::SHOP)
{
}

ShopScene::~ShopScene()
{
}

void ShopScene::Awake()
{
	Scene::Awake();
}

void ShopScene::Start()
{
	Scene::Start();
}

void ShopScene::Update()
{
	Scene::Update();
}

void ShopScene::LateUpdate()
{
	Scene::LateUpdate();
}

void ShopScene::FinalUpdate()
{
	Scene::FinalUpdate();
}

void ShopScene::Render()
{
	Scene::Render();
}

void ShopScene::Enter()
{
	ShowCursor(false);
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	Load(L"..\\Resources\\Map\\ShopMap.map");
}

void ShopScene::Exit()
{
}
