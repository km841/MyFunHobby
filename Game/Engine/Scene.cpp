#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Camera.h"
#include "Physics.h"

Scene::Scene(SCENE_TYPE eSceneType)
	: m_eSceneType(eSceneType)
{

}

Scene::~Scene()
{
}

void Scene::Awake()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const shared_ptr<GameObject>& pGameObject : m_vGameObjects)
	{
		if (pGameObject)
			pGameObject->FinalUpdate();
	}
}

void Scene::Render()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView();
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTarget();

	for (const shared_ptr<Camera>& pCamera : m_vCameras)
	{
		pCamera->Render();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> pGameObject)
{
	if (pGameObject->GetCamera())
		m_vCameras.push_back(pGameObject->GetCamera());

	m_vGameObjects.push_back(pGameObject);
}
