#include "pch.h"
#include "Scenes.h"
#include "TitleScene.h"
#include "TownScene.h"
#include "ToolScene.h"
#include "DungeonScene.h"
#include "Engine.h"
#include "Camera.h"

void Scenes::Init()
{
	m_arrScenes[static_cast<uint8>(SCENE_TYPE::TITLE)] = make_shared<TitleScene>();
	m_arrScenes[static_cast<uint8>(SCENE_TYPE::TOWN)] = make_shared<TownScene>();
	m_arrScenes[static_cast<uint8>(SCENE_TYPE::TOOL)] = make_shared<ToolScene>();
	m_arrScenes[static_cast<uint8>(SCENE_TYPE::DUNGEON)] = make_shared<DungeonScene>();

	m_pActiveScene = m_arrScenes[static_cast<uint8>(SCENE_TYPE::TITLE)];
	m_pActiveScene->Enter();
}

void Scenes::Awake()
{
	m_pActiveScene->Awake();
}

void Scenes::Start()
{
	m_pActiveScene->Start();
}

void Scenes::Update()
{
	m_pActiveScene->Update();
	m_pActiveScene->LateUpdate();
	m_pActiveScene->FinalUpdate();
}

void Scenes::Render()
{
	m_pActiveScene->Render();
}

void Scenes::ChangeScene(SCENE_TYPE eSceneType)
{
	if (m_pActiveScene)
	{
		m_pActiveScene->Exit();
	}

	m_pActiveScene = m_arrScenes[static_cast<uint8>(eSceneType)];
	m_pActiveScene->Enter();
}

Vec3 Scenes::ScreenToWorldPosition(const Vec3& vPoint, shared_ptr<Camera> pCamera)
{
	int32 iWidth  = g_pEngine->GetWidth();
	int32 iHeight = g_pEngine->GetHeight();

	Matrix matProjection = pCamera->GetProjectionMatrix();

	float fViewX = (+2.f * vPoint.x / iWidth  - 1) / matProjection(0, 0);
	float fViewY = (-2.f * vPoint.y / iHeight + 1) / matProjection(1, 1);

	Matrix matViewInv = pCamera->GetViewMatrix().Invert();

	Vec3 vWorldPos = Vec3(fViewX, fViewY, vPoint.z);
	vWorldPos = XMVector3TransformCoord(vWorldPos, matViewInv);

	return vWorldPos;
}

Vec3 Scenes::WorldToScreenPosition(const Vec3& vPoint, shared_ptr<Camera> pCamera)
{
	int32 iWidth = g_pEngine->GetWidth();
	int32 iHeight = g_pEngine->GetHeight();

	Matrix matView = pCamera->GetViewMatrix();
	Matrix matProjection = pCamera->GetProjectionMatrix();
	Matrix matFinal = matView * matProjection;

	Vec3 vScreenPos = XMVector3TransformCoord(vPoint, matFinal);

	vScreenPos.x = iWidth  * ((vScreenPos.x + 1)   / 2.f);
	vScreenPos.y = iHeight * ((1.f - vScreenPos.y) / 2.f);
	vScreenPos.z = vPoint.z;
	return vScreenPos;
}
