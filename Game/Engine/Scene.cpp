#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"
#include "Camera.h"
#include "Physics.h"
#include "Tile.h"
#include "Resources.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "DebugRenderer.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "HUD.h"
#include "UI.h"
#include "AfterImage.h"
#include "Light.h"
#include "ObjectFactory.h"
#include "Clock.h"
#include "Player.h"
#include "ComponentObject.h"
#include "Font.h"
#include "Background.h"
#include "DungeonGate.h"
#include "Animator.h"
#include "Animation.h"
#include "ObjectRemoveToSceneEvent.h"
#include "DungeonWall.h"
#include "LightObject.h"
#include "Input.h"

std::array<std::vector<shared_ptr<GameObject>>, GLOBAL_OBJECT_TYPE_COUNT> Scene::s_vGlobalObjects;
std::vector<shared_ptr<Camera>> Scene::s_vCameras;
std::vector<shared_ptr<Light>> Scene::s_vLights;

Scene::Scene(SCENE_TYPE eSceneType)
	: m_eSceneType(eSceneType)
	, m_fFadeEffectRatio(1.f)
	, m_eActiveSceneEvent(EVENT_TYPE::END)
	, m_fAccTime(0.f)
	, m_bDebugMode(false)
{

}

Scene::~Scene()
{
}

void Scene::Awake()
{
	AwakeLocalObjects();
	AwakeGlobalObjects();
}

void Scene::Start()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Start();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Start();
		}
	}
}

void Scene::Update()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Update();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Update();
		}
	}

	EventUpdate();
	CameraShakeUpdate();

	if (IS_DOWN(KEY_TYPE::O))
	{
		GetMainCamera().lock()->GetCamera()->FlipDebugMode();
	}
}

void Scene::LateUpdate()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->LateUpdate();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->LateUpdate();
		}
	}
}

void Scene::FinalUpdate()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->FinalUpdate();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->FinalUpdate();
		}
	}
}

void Scene::Render()
{
	// RenderTarget Clear
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->ClearRenderTargetView();
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->ClearRenderTargetView();
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView();

	// G-Buffer Writing
	Render_Deferred();

	// Light Rendering
	PushLightData();
	Render_Lights();

	// G-Buffer Merge & Rendering
	Render_Final();

	// Forward Rendering
	Render_Forward();

	// Font Rendering
	Render_Font();
}

void Scene::Destroy()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Destroy();
		}
	}

	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Destroy();
		}
	}
}

void Scene::Render_Lights()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->OMSetRenderTarget();
	shared_ptr<Camera> pMainCamera = s_vCameras[0];

	for (auto& pLight : s_vLights)
	{
		pLight->Render(pMainCamera);
	}

	for (auto& pLight : m_vLights)
	{
		pLight->Render(pMainCamera);
	}
}

void Scene::Render_Final()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTarget(1);

	if (EVENT_TYPE::SCENE_FADE_EVENT == m_eActiveSceneEvent)
		GET_SINGLE(Resources)->Get<Material>(L"Final")->SetFloat(0, m_fFadeEffectRatio);
	else
		GET_SINGLE(Resources)->Get<Material>(L"Final")->SetFloat(0, 1.f);

	GET_SINGLE(Resources)->Get<Material>(L"Final")->PushGraphicData();
	GET_SINGLE(Resources)->LoadRectMesh()->Render();
}

void Scene::Render_Forward()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTarget(1);
	shared_ptr<Camera> pCamera = s_vCameras[0];
	pCamera->Render_Forward();

	for (const shared_ptr<Camera>& pSubCamera : s_vCameras)
	{
		if (pCamera == pSubCamera)
			continue;

		pSubCamera->SortGameObject();
		pSubCamera->Render_Forward();
	}
}

void Scene::Render_Deferred()
{
	shared_ptr<Camera> pCamera = s_vCameras[0];
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->OMSetRenderTarget();
	pCamera->SortGameObject();
	pCamera->Render_Deferred();

	for (const shared_ptr<Camera>& pSubCamera : s_vCameras)
	{
		if (pCamera == pSubCamera)
			continue;

		pSubCamera->SortGameObject();
		pSubCamera->Render_Deferred();
	}
}

void Scene::Render_Font()
{
	FONT->Render();
}

void Scene::PushLightData()
{
	LightParams lightParams = {};

	for (auto& pLight : m_vLights)
	{
		const LightInfo& lightInfo = pLight->GetLightInfo();

		pLight->SetLightIndex(lightParams.iLightCount);

		lightParams.Lights[lightParams.iLightCount] = lightInfo;
		lightParams.iLightCount++;
	}

	for (auto& pLight : s_vLights)
	{
		const LightInfo& lightInfo = pLight->GetLightInfo();

		pLight->SetLightIndex(lightParams.iLightCount);

		lightParams.Lights[lightParams.iLightCount] = lightInfo;
		lightParams.iLightCount++;
	}

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::LIGHT)->PushData(&lightParams, sizeof(lightParams));
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::LIGHT)->Mapping();
}

void Scene::EventUpdate()
{
	// Processing Scene Event
	if (EVENT_TYPE::END == m_eActiveSceneEvent)
	{
		if (!m_vSceneEvents.empty())
		{
			const auto& curEvent = m_vSceneEvents.front();
			m_eActiveSceneEvent = curEvent.eEventType;
		}
	}

	else
	{

		auto& curEvent = m_vSceneEvents.front();
		switch (m_eActiveSceneEvent)
		{
		case EVENT_TYPE::SCENE_FADE_EVENT:
		{
			SCENE_FADE_EFFECT eSceneFadeEffect = static_cast<SCENE_FADE_EFFECT>(curEvent.iDetailEnum);
			curEvent.fCurTime += WORLD_DELTA_TIME;

			if (SCENE_FADE_EFFECT::FADE_IN == eSceneFadeEffect)
				m_fFadeEffectRatio = curEvent.fCurTime / curEvent.fEndTime;

			else if (SCENE_FADE_EFFECT::FADE_OUT == eSceneFadeEffect)
				m_fFadeEffectRatio = 1.f - (curEvent.fCurTime / curEvent.fEndTime);

			else if (SCENE_FADE_EFFECT::WHITE_FADE_IN == eSceneFadeEffect)
				m_fFadeEffectRatio = 1.f + (1.f - (curEvent.fCurTime / curEvent.fEndTime));


			if (curEvent.fEndTime < curEvent.fCurTime)
			{
				m_fFadeEffectRatio = 1.f;
				m_eActiveSceneEvent = EVENT_TYPE::END;
				m_vSceneEvents.erase(m_vSceneEvents.begin());
			}
		}
			break;

		case EVENT_TYPE::ACTIVATE_DISTORTION:
		{
			curEvent.fCurTime += WORLD_DELTA_TIME;
			GET_SINGLE(Resources)->Get<Material>(L"Final")->SetFloat(1, curEvent.fCurTime);
			GET_SINGLE(Resources)->Get<Material>(L"Final")->SetFloat(2, 1.f - curEvent.fCurTime / curEvent.fEndTime);
			GET_SINGLE(Resources)->Get<Material>(L"Final")->SetInt(0, 1); // Distortion Flag

			if (curEvent.fEndTime < curEvent.fCurTime)
			{
				GET_SINGLE(Resources)->Get<Material>(L"Final")->SetInt(0, 0); // Distortion Flag
				m_eActiveSceneEvent = EVENT_TYPE::END;
				m_vSceneEvents.erase(m_vSceneEvents.begin());
			}
		}
			break;

		case EVENT_TYPE::ACTIVATE_AFTEREFFECT:
		{
			curEvent.fCurTime += WORLD_DELTA_TIME;
			GET_SINGLE(Resources)->Get<Material>(L"Final")->SetFloat(1, m_fAccTime);
			GET_SINGLE(Resources)->Get<Material>(L"Final")->SetInt(1, 1); // AfterEffect Flag

			if (curEvent.fEndTime < curEvent.fCurTime)
			{
				GET_SINGLE(Resources)->Get<Material>(L"Final")->SetInt(1, 0); // AfterEffect Flag
				m_eActiveSceneEvent = EVENT_TYPE::END;
				m_vSceneEvents.erase(m_vSceneEvents.begin());
			}
		}
			break;
		}
	}
}

void Scene::CameraShakeUpdate()
{
	if (m_qCameraShakeInfo.empty())
		return;

	if (m_ActiveCameraShakeInfo.vCameraShakeImpulse == Vec3::Zero)
	{
		m_ActiveCameraShakeInfo = m_qCameraShakeInfo.front();
		m_ActiveCameraShakeInfo.tCameraShakeTimer.Start();
	}

	if (m_ActiveCameraShakeInfo.tCameraShakeTimer.IsRunning())
	{
		m_ActiveCameraShakeInfo.tCameraShakeTimer.Update(WORLD_DELTA_TIME);
		float fProgress = m_ActiveCameraShakeInfo.tCameraShakeTimer.GetProgress();

		shared_ptr<Camera> pMainCamera = s_vCameras[0];
		if (!pMainCamera)
			return;

		Vec3 vCamPos = pMainCamera->GetTransform()->GetLocalPosition();
		if (fProgress < 0.5f)
		{
			vCamPos += m_ActiveCameraShakeInfo.vCameraShakeImpulse * WORLD_DELTA_TIME;
			pMainCamera->GetTransform()->SetLocalPosition(vCamPos);
		}
		else
		{
			vCamPos -= m_ActiveCameraShakeInfo.vCameraShakeImpulse * WORLD_DELTA_TIME;
			pMainCamera->GetTransform()->SetLocalPosition(vCamPos);

			if (m_ActiveCameraShakeInfo.tCameraShakeTimer.IsFinished())
			{
				m_ActiveCameraShakeInfo.tCameraShakeTimer.Stop();
				m_ActiveCameraShakeInfo.vCameraShakeImpulse = Vec3::Zero;
				m_qCameraShakeInfo.pop();
			}
		}
	}
}

void Scene::RemoveSceneEvent()
{
	m_vSceneEvents.clear();
	m_eActiveSceneEvent = EVENT_TYPE::END;
}

void Scene::AddGameObject(shared_ptr<GameObject> pGameObject)
{
	uint8 iLayerType = static_cast<uint8>(pGameObject->GetLayerType());

	if (pGameObject->GetPhysical())
		pGameObject->GetPhysical()->AddActorToPxScene();

	if (pGameObject->GetCamera())
		s_vCameras.push_back(pGameObject->GetCamera());
	
	if (iLayerType < SCENE_OBJECT_TYPE_COUNT)
	{
		m_vSceneObjects[iLayerType].push_back(pGameObject);

		if (pGameObject->GetLight())
			m_vLights.push_back(pGameObject->GetLight());
	}

	else
	{
		s_vGlobalObjects[iLayerType - SCENE_OBJECT_TYPE_COUNT].push_back(pGameObject);

		if (pGameObject->GetLight())
			s_vLights.push_back(pGameObject->GetLight());
	}
}

std::vector<shared_ptr<GameObject>>& Scene::GetGameObjects(LAYER_TYPE eLayerType)
{
	uint8 iLayerType = static_cast<uint8>(eLayerType);
	assert(iLayerType < LAYER_TYPE_COUNT);


	if (iLayerType < SCENE_OBJECT_TYPE_COUNT)
		return m_vSceneObjects[iLayerType];
	else
		return s_vGlobalObjects[iLayerType - SCENE_OBJECT_TYPE_COUNT];
}

void Scene::RemoveGameObject(shared_ptr<GameObject> pGameObject)
{
	uint8 iLayerType = static_cast<uint8>(pGameObject->GetLayerType());

	if (pGameObject->GetCamera())
	{
		auto pFindIt = std::find(s_vCameras.begin(), s_vCameras.end(), pGameObject->GetCamera());
		if (pFindIt != s_vCameras.end())
			s_vCameras.erase(pFindIt);
	}

	if (pGameObject->GetLight())
	{
		if (iLayerType < SCENE_OBJECT_TYPE_COUNT)
		{
			auto pFindIt = std::find(m_vLights.begin(), m_vLights.end(), pGameObject->GetLight());
			if (pFindIt != m_vLights.end())
				m_vLights.erase(pFindIt);
		}
		else
		{
			auto pFindIt = std::find(s_vLights.begin(), s_vLights.end(), pGameObject->GetLight());
			if (pFindIt != s_vLights.end())
				s_vLights.erase(pFindIt);
		}

	}

	auto& vGameObjects = GetGameObjects(pGameObject->GetLayerType());
	
	auto pFindIt = std::find(vGameObjects.begin(), vGameObjects.end(), pGameObject);
	if (pFindIt != vGameObjects.end())
	{
		if (pFindIt->get()->GetPhysical())
		{
			pFindIt->get()->GetPhysical()->GetActor<PxRigidActor>()->userData = nullptr;
			pFindIt->get()->GetPhysical()->RemoveActorToPxScene();
		}

		vGameObjects.erase(pFindIt);
	}

}

void Scene::ShakeCameraAxis(float fMaxTime, const Vec3& vImpulse)
{
	m_qCameraShakeInfo.push(CameraShakeInfo{ fMaxTime , vImpulse });
}

bool Scene::IsExistTileThisPos(const Vec2& vTilePos)
{
	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);
	const auto& pMainCamera = GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera();

	for (const auto& pGameObject : vGameObjects)
	{
		if (TILE_TYPE::NONE == static_pointer_cast<Tile>(pGameObject)->GetTileType())
			continue;

		Vec3 vPos = pGameObject->GetTransform()->GetPhysicalPosition();

		if (vTilePos.x == vPos.x &&
			vTilePos.y == vPos.y)
			return true;
	}

	return false;
}

bool Scene::RaycastToTileGroup(shared_ptr<GameObject> pGameObject, const Vec3& vOrigin, const Vec3& vDir, float fMaxDistance)
{
	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);

	for (const auto& pTile : vGameObjects)
	{
		if (TILE_TYPE::WALL != static_pointer_cast<Tile>(pGameObject)->GetTileType())
			continue;

		if (pGameObject->GetCollider()->Raycast(vOrigin, vDir, pTile, fMaxDistance))
			return true;
	}

	return false;
}

void Scene::RemoveLocalGroup(LAYER_TYPE eLocalLayerType)
{
	auto& vLocalGroup = GetGameObjects(eLocalLayerType);

	for (auto& pLocalGameObject : vLocalGroup)
	{
		if (pLocalGameObject->GetPhysical())
			pLocalGameObject->GetPhysical()->RemoveActorToPxScene();

		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(pLocalGameObject, m_eSceneType));
	}
}

Vec4 Scene::GetObjectLimitRect()
{
	float fMinX = 0.f;
	float fMaxX = 0.f;
	float fMinY = 0.f;
	float fMaxY = 0.f;

	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (!pGameObject->GetTransform())
				continue;

			Vec3 vPos = Vec3::Zero;
			Vec3 vSize = pGameObject->GetTransform()->GetLocalScale();
			if (pGameObject->GetPhysical())
				vPos = pGameObject->GetTransform()->GetPhysicalPosition();
			
			else
				vPos = pGameObject->GetTransform()->GetLocalPosition();

			if (Vec3::Zero == vPos)
				continue;
			
			fMinX = std::min(fMinX, vPos.x - vSize.x / 2.f);
			fMinY = std::min(fMinY, vPos.y + vSize.y / 2.f);
			fMaxX = std::max(fMaxX, vPos.x + vSize.x / 2.f);
			fMaxY = std::max(fMaxY, vPos.y - vSize.y / 2.f);
		}
	}

	return Vec4(fMinX, fMinY, fMaxX, fMaxY);
}

std::vector<DUNGEON_TYPE> Scene::GetDungeonGateTypesFromMapFile(const wstring& szPath)
{
	std::vector<DUNGEON_TYPE> vDungeonGateTypes = {};
	std::wifstream ifs(szPath, std::ios::in);

#pragma region PASS
	{
		uint32 iBGCount = 0;
		ifs >> iBGCount;

		for (uint32 i = 0; i < iBGCount; ++i)
		{
			wstring szTexPath = {};
			Vec3 vBGPosition = {};
			Vec3 vBGScale = {};
			Vec3 vBGSpeed = {};

			ifs >> szTexPath;
			ifs.ignore(1);
			ifs >> vBGPosition.x >> vBGPosition.y >> vBGPosition.z;
			ifs.ignore(1);
			ifs >> vBGScale.x >> vBGScale.y >> vBGScale.z;
			ifs.ignore(1);
			ifs >> vBGSpeed.x >> vBGSpeed.y >> vBGSpeed.z;
			ifs.ignore(1);
		}

		uint32 iCount = 0;
		wstring szTexPath = {};
		Vec2 vTileAlignVec = {};

		ifs >> iCount;
		ifs.ignore(1);

		assert(iCount != 0);
		for (uint32 i = 0; i < iCount; ++i)
		{
			wstring szTexPath;
			Vec3 vTileAlignVec;
			int32 iTileType;

			ifs >> iTileType;
			ifs.ignore(1);
			ifs >> szTexPath;
			ifs.ignore(1);
			ifs >> vTileAlignVec.x >> vTileAlignVec.y;
			ifs.ignore(1);
		}
	}


	uint32 iDungeonObjectCount = 0;
	ifs >> iDungeonObjectCount;

	for (uint32 i = 0; i < iDungeonObjectCount; ++i)
	{
		uint32 iDungeonObjTypeEnum = 0;
		uint32 iStageKindEnum = 0;
		uint32 iDungeonTypeEnum = 0;

		wstring szTexPath = {};
		Vec3 vPos = {};

		ifs >> iDungeonObjTypeEnum;
		ifs.ignore(1);

		ifs >> iStageKindEnum;
		ifs.ignore(1);

		ifs >> iDungeonTypeEnum;
		ifs.ignore(1);

		ifs >> szTexPath;
		ifs.ignore(1);

		ifs >> vPos.x >> vPos.y;
		ifs.ignore(1);
#pragma endregion
		STAGE_KIND eStageKind = static_cast<STAGE_KIND>(iStageKindEnum);
		DUNGEON_TYPE eDungeonType = static_cast<DUNGEON_TYPE>(iDungeonTypeEnum);
		if (!iDungeonObjTypeEnum) // 0 == DungeonGate
			vDungeonGateTypes.push_back(eDungeonType);
	}

	return vDungeonGateTypes;
}

void Scene::LoadBackground(std::wifstream& ifs)
{
	uint32 iBGCount = 0;
	ifs >> iBGCount;

	for (uint32 i = 0; i < iBGCount; ++i)
	{
		wstring szTexPath = {};
		Vec3 vBGPosition = {};
		Vec3 vBGScale = {};
		Vec3 vBGSpeed = {};

		ifs >> szTexPath;
		ifs.ignore(1);
		ifs >> vBGPosition.x >> vBGPosition.y >> vBGPosition.z;
		ifs.ignore(1);
		ifs >> vBGScale.x >> vBGScale.y >> vBGScale.z;
		ifs.ignore(1);
		ifs >> vBGSpeed.x >> vBGSpeed.y >> vBGSpeed.z;
		ifs.ignore(1);

		shared_ptr<Background> pBackground = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(L"Deferred", szTexPath);
		pBackground->GetTransform()->SetLocalPosition(vBGPosition);
		pBackground->GetTransform()->SetLocalScale(vBGScale);
		pBackground->SetFollowSpeed(vBGSpeed);

		pBackground->SetFrustum(false);
		pBackground->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pBackground, m_eSceneType));
	}
}

void Scene::LoadTile(std::wifstream& ifs)
{
	uint32 iCount = 0;
	wstring szTexPath = {};
	Vec2 vTileAlignVec = {};

	ifs >> iCount;
	ifs.ignore(1);

	assert(iCount != 0);
	for (uint32 i = 0; i < iCount; ++i)
	{
		wstring szTexPath;
		Vec3 vTileAlignVec;
		int32 iTileType;

		ifs >> iTileType;
		ifs.ignore(1);
		ifs >> szTexPath;
		ifs.ignore(1);
		ifs >> vTileAlignVec.x >> vTileAlignVec.y;
		ifs.ignore(1);

		TILE_TYPE eTileType = static_cast<TILE_TYPE>(iTileType);
		CreateTile(eTileType, szTexPath, vTileAlignVec);
	}
}

void Scene::LoadDungeonObject(std::wifstream& ifs)
{
	uint32 iDungeonObjectCount = 0;
	ifs >> iDungeonObjectCount;

	for (uint32 i = 0; i < iDungeonObjectCount; ++i)
	{
		uint32 iDungeonObjTypeEnum = 0;
		uint32 iStageKindEnum = 0;
		uint32 iDungeonTypeEnum = 0;

		wstring szTexPath = {};
		Vec3 vPos = {};

		ifs >> iDungeonObjTypeEnum;
		ifs.ignore(1);

		ifs >> iStageKindEnum;
		ifs.ignore(1);

		ifs >> iDungeonTypeEnum;
		ifs.ignore(1);

		ifs >> szTexPath;
		ifs.ignore(1);

		ifs >> vPos.x >> vPos.y;
		ifs.ignore(1);

		STAGE_KIND eStageKind = static_cast<STAGE_KIND>(iStageKindEnum);
		DUNGEON_TYPE eDungeonType = static_cast<DUNGEON_TYPE>(iDungeonTypeEnum);

		switch (static_cast<DUNGEON_OBJ_TYPE>(iDungeonObjTypeEnum))
		{
		case DUNGEON_OBJ_TYPE::DUNGEON_GATE:
			CreateDungeonGate(eStageKind, eDungeonType, szTexPath, vPos);
			break;

		case DUNGEON_OBJ_TYPE::DUNGEON_WALL:
			CreateDungeonWall(eStageKind, szTexPath, vPos);
			break;
		}
	}
}

void Scene::LoadDecoObject(std::wifstream& ifs)
{
	uint32 iDecoObjectCount = 0;
	ifs >> iDecoObjectCount;

	for (uint32 i = 0; i < iDecoObjectCount; ++i)
	{
		uint32 iDecoObjTypeEnum = 0;

		wstring szTexPath = {};
		Vec3 vPos = {};

		ifs >> iDecoObjTypeEnum;
		ifs.ignore(1);

		ifs >> szTexPath;
		ifs.ignore(1);

		ifs >> vPos.x >> vPos.y;
		ifs.ignore(1);

		DECO_OBJECT_TYPE eDecoObjectType = static_cast<DECO_OBJECT_TYPE>(iDecoObjTypeEnum);
		CreateDecoObject(eDecoObjectType, szTexPath, vPos);
	}
}

void Scene::LoadLightObject(std::wifstream& ifs)
{
	uint32 iLightObjectCount = 0;
	ifs >> iLightObjectCount;

	for (uint32 i = 0; i < iLightObjectCount; ++i)
	{
		Vec3 vDiffuse = {};
		Vec3 vAmbient = {};
		float fRange = 0.f;
		Vec3 vPos = {};

		ifs >> vDiffuse.x >> vDiffuse.y >> vDiffuse.z;
		ifs.ignore(1);

		ifs >> vAmbient.x >> vAmbient.y >> vAmbient.z;
		ifs.ignore(1);

		ifs >> fRange;
		ifs.ignore(1);

		ifs >> vPos.x >> vPos.y >> vPos.z;
		ifs.ignore(1);

		CreateLightObject(vDiffuse, vAmbient, fRange, vPos);
	}
}

void Scene::CreateDungeonGate(STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType, const wstring& szTexPath, const Vec3& vPos)
{
	// 애니메이션 추가
	shared_ptr<DungeonGate> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DungeonGate>(
		L"Deferred", false, ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(150.f, 120.f, 1.f), MassProperties(), L"", eStageKind, eDungeonType);

	shared_ptr<Animation> pActivateAnimation = nullptr;
	shared_ptr<Animation> pDeactivateAnimation = nullptr;

	if (STAGE_KIND::BLACK_LAB == eStageKind)
	{
		switch (eDungeonType)
		{
		case DUNGEON_TYPE::BASE_CAMP:
			break;
		case DUNGEON_TYPE::DUNGEON_ITEM:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Item_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Item\\ch3dungeongate_item_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Item_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Item\\ch3dungeongate_item_deactivate.anim");
			pGameObject->GetTransform()->SetGlobalOffset(Vec2(0.f, 15.f));
			break;
		case DUNGEON_TYPE::DUNGEON_GOLD:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Gold_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Gold\\ch3dungeongate_gold_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Gold_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Gold\\ch3dungeongate_gold_deactivate.anim");
			break;
		case DUNGEON_TYPE::DUNGEON_BONE:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Bone_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Bone\\ch3dungeongate_bone_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Bone_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Bone\\ch3dungeongate_bone_deactivate.anim");
			break;
		case DUNGEON_TYPE::SHOP:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Shop_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Shop\\ch3dungeongate_shop_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Shop_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Shop\\ch3dungeongate_shop_deactivate.anim");
			break;
		case DUNGEON_TYPE::VICE_BOSS:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_ViceBoss_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\ViceBoss\\ch3dungeongate_viceboss_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_ViceBoss_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\ViceBoss\\ch3dungeongate_viceboss_deactivate.anim");
			break;
		case DUNGEON_TYPE::STAGE_BOSS:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Boss_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Boss\\ch3dungeongate_boss_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Boss_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Boss\\ch3dungeongate_boss_deactivate.anim");
			break;
		}
	}

	else if (STAGE_KIND::CITADEL_OF_FATE == eStageKind)
	{
		switch (eDungeonType)
		{
		case DUNGEON_TYPE::BASE_CAMP:
			break;
		case DUNGEON_TYPE::DUNGEON_ITEM:
			break;
		case DUNGEON_TYPE::DUNGEON_GOLD:
			break;
		case DUNGEON_TYPE::DUNGEON_BONE:
			break;
		case DUNGEON_TYPE::VICE_BOSS:
			break;
		case DUNGEON_TYPE::STAGE_BOSS:
			break;
		}
	}

	assert(pActivateAnimation && pDeactivateAnimation);

	pGameObject->AddComponent(make_shared<Animator>());
	pGameObject->GetAnimator()->AddAnimation(L"DungeonGate_Activate", pActivateAnimation);
	pGameObject->GetAnimator()->AddAnimation(L"DungeonGate_Deactivate", pDeactivateAnimation);
	pGameObject->GetAnimator()->Play(L"DungeonGate_Deactivate");

	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTexPath, szTexPath);
	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	pGameObject->GetTransform()->SetLocalPosition(Vec3(vPos.x, vPos.y, 100.5f));

	pGameObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, m_eSceneType));
}

void Scene::CreateDungeonWall(STAGE_KIND eStageKind, const wstring& szTexPath, const Vec3& vPos)
{
	shared_ptr<DungeonWall> pDungeonWall = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DungeonWall>(L"Deferred", szTexPath, eStageKind);
	pDungeonWall->GetTransform()->SetLocalPosition(Vec3(vPos.x, vPos.y, 102.f));

	pDungeonWall->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDungeonWall, m_eSceneType));
}

void Scene::CreateTile(TILE_TYPE eTileType, const wstring& szTexPath, const Vec3& vPos)
{
	shared_ptr<Tile> pTile = nullptr;
	int32 iTileType = static_cast<int32>(eTileType);
	if (TILE_TYPE::NONE == eTileType)
	{
		pTile = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<Tile>(
			L"Deferred", szTexPath, iTileType);
	}
	else
	{
		pTile = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<Tile>(
			L"Deferred",
			false,
			ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 50.f), MassProperties(100.f, 100.f, 0.1f),
			szTexPath, iTileType);
	}

	pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
	pTile->GetTransform()->SetLocalPosition(Vec3(vPos.x, vPos.y, 101.f));

	// 잠들어 있는 Component 깨우기
	pTile->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));
}

void Scene::CreateDecoObject(DECO_OBJECT_TYPE eDecoObjType, const wstring szTexPath, const Vec3& vPos)
{
	shared_ptr<DecoObject> pDecoObject = nullptr;

	switch (eDecoObjType)
	{
	case DECO_OBJECT_TYPE::NORMAL:
		pDecoObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DecoObject>(L"Deferred", szTexPath);
		break;
	}

	assert(pDecoObject);
	pDecoObject->GetTransform()->SetLocalPosition(Vec3(vPos.x, vPos.y, 100.5f));
	pDecoObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDecoObject, m_eSceneType));
}

void Scene::CreateLightObject(const Vec3& vDiffuse, const Vec3& vAmbient, float fRange, const Vec3& vPos)
{
	shared_ptr<LightObject> pLightObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LightObject>(L"Deferred");

	pLightObject->AddComponent(make_shared<Light>());
	pLightObject->GetLight()->SetDiffuse(vDiffuse);
	pLightObject->GetLight()->SetAmbient(vAmbient);
	pLightObject->GetLight()->SetLightRange(fRange);
	pLightObject->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	pLightObject->GetTransform()->SetLocalPosition(vPos);
	pLightObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLightObject, m_eSceneType));
}

weak_ptr<ComponentObject> Scene::GetMainCamera()
{
	assert(!s_vCameras.empty());
	weak_ptr<Camera> pMainCamera = s_vCameras[0];
	return static_pointer_cast<ComponentObject>(pMainCamera.lock()->GetGameObject());
}

weak_ptr<ComponentObject> Scene::GetUICamera()
{
	assert(!s_vCameras.empty());
	weak_ptr<Camera> pUICamera = s_vCameras[1];
	return static_pointer_cast<ComponentObject>(pUICamera.lock()->GetGameObject());
}

shared_ptr<Player> Scene::GetPlayer()
{
	auto& vGameObjects = GetGameObjects(LAYER_TYPE::PLAYER);
	if (vGameObjects.empty())
		return nullptr;

	return static_pointer_cast<Player>(vGameObjects[0]);
}

void Scene::Load(const wstring& szPath)
{
	std::wifstream ifs(szPath, std::ios::in);

	LoadBackground(ifs);
	LoadTile(ifs);
	LoadDungeonObject(ifs);
	LoadDecoObject(ifs);
	LoadLightObject(ifs);

	ifs.close();
}

void Scene::AwakeLocalObjects()
{
	for (int32 i = 0; i < SCENE_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject>& pGameObject : m_vSceneObjects[i])
		{
			if (pGameObject)
				pGameObject->Awake();
		}
	}
}

void Scene::AwakeGlobalObjects()
{
	for (int32 i = 0; i < GLOBAL_OBJECT_TYPE_COUNT; ++i)
	{
		for (const shared_ptr<GameObject> pGameObject : s_vGlobalObjects[i])
		{
			if (pGameObject)
				pGameObject->Awake();
		}
	}
}
