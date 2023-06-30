#include "pch.h"
#include "EndingScene.h"

EndingScene::EndingScene()
	: Scene(SCENE_TYPE::ENDING)
{
}

EndingScene::~EndingScene()
{
}

void EndingScene::Awake()
{
	Scene::Awake();
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

	Awake();
}

void EndingScene::Exit()
{
}
