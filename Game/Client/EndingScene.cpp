#include "pch.h"
#include "EndingScene.h"
#include "InterfaceManager.h"
#include "HUD.h"

EndingScene::EndingScene()
	: Scene(SCENE_TYPE::ENDING)
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::Awake()
{
	AwakeLocalObjects();
}

void EndingScene::Start()
{
	Scene::Start();
}

void EndingScene::Update()
{
	Scene::Update();
}

void EndingScene::LateUpdate()
{
	Scene::LateUpdate();
}

void EndingScene::FinalUpdate()
{
	Scene::FinalUpdate();
}

void EndingScene::Render()
{
	Scene::Render();
}

void EndingScene::Enter()
{
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::ENDING)->Action();


	Awake();
}

void EndingScene::Exit()
{
}
