#include "pch.h"
#include "ShopScene.h"
#include "Engine.h"
#include "Player.h"
#include "ComponentObject.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"

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
	InitializeCameraAndPlayerPos();
	ShowCursor(false);
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	Load(L"..\\Resources\\Map\\ShopMap.map");
}

void ShopScene::Exit()
{
}

void ShopScene::InitializeCameraAndPlayerPos()
{
	weak_ptr<Player> pPlayer = GetPlayer();

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	pPlayer.lock()->GetTransform()->SetPhysicalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 200.f, 100.f));
	GetMainCamera().lock()->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 500.f, 1.f));
	GetBGCamera().lock()->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 500.f, 1.f));
}
