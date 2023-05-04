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

std::array<std::vector<shared_ptr<GameObject>>, GLOBAL_OBJECT_TYPE_COUNT> Scene::s_vGlobalObjects;
std::vector<shared_ptr<Camera>> Scene::s_vCameras;
std::vector<shared_ptr<Light>> Scene::s_vLights;

Scene::Scene(SCENE_TYPE eSceneType)
	: m_eSceneType(eSceneType)
	, m_fFadeEffectRatio(1.f)
	, m_eActiveSceneEvent(EVENT_TYPE::END)
	, m_tCameraShakeTimer(0)
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

void Scene::Render_Lights()
{
	g_pEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->OMSetRenderTarget();
	shared_ptr<Camera> pMainCamera = s_vCameras[0];
	for (auto& pLight : s_vLights)
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
		switch (m_eActiveSceneEvent)
		{
		case EVENT_TYPE::SCENE_FADE_EVENT:
		{
			auto& curEvent = m_vSceneEvents.front();
			SCENE_FADE_EFFECT eSceneFadeEffect = static_cast<SCENE_FADE_EFFECT>(curEvent.iDetailEnum);
			curEvent.fCurTime += DELTA_TIME;

			if (SCENE_FADE_EFFECT::FADE_IN == eSceneFadeEffect)
				m_fFadeEffectRatio = curEvent.fCurTime / curEvent.fEndTime;

			else // FADE_OUT
				m_fFadeEffectRatio = 1.f - (curEvent.fCurTime / curEvent.fEndTime);


			if (curEvent.fEndTime < curEvent.fCurTime)
			{
				m_fFadeEffectRatio = 1.f;
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
	if (m_tCameraShakeTimer.IsRunning())
	{
		m_tCameraShakeTimer.Update(DELTA_TIME);
		float fProgress = m_tCameraShakeTimer.GetProgress();
		shared_ptr<Camera> pMainCamera = s_vCameras[0];
		if (!pMainCamera)
			return;

		Vec3 vCamPos = pMainCamera->GetTransform()->GetLocalPosition();
		if (fProgress < 0.5f)
		{
			vCamPos += m_vCameraShakeImpulse * DELTA_TIME;
			pMainCamera->GetTransform()->SetLocalPosition(vCamPos);
		}
		else
		{
			vCamPos -= m_vCameraShakeImpulse * DELTA_TIME;
			pMainCamera->GetTransform()->SetLocalPosition(vCamPos);

			if (m_tCameraShakeTimer.IsFinished())
			{
				m_tCameraShakeTimer.Stop();
				m_vCameraShakeImpulse = Vec3::Zero;
			}
		}
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> pGameObject)
{
	if (pGameObject->GetCamera())
		s_vCameras.push_back(pGameObject->GetCamera());

	if (pGameObject->GetLight())
		s_vLights.push_back(pGameObject->GetLight());

	if (pGameObject->GetPhysical())
		pGameObject->GetPhysical()->AddActorToPxScene();
	

	uint8 iLayerType = static_cast<uint8>(pGameObject->GetLayerType());

	if (iLayerType < SCENE_OBJECT_TYPE_COUNT)
		m_vSceneObjects[iLayerType].push_back(pGameObject);

	else
		s_vGlobalObjects[iLayerType - SCENE_OBJECT_TYPE_COUNT].push_back(pGameObject);
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
	if (pGameObject->GetCamera())
	{
		auto pFindIt = std::find(s_vCameras.begin(), s_vCameras.end(), pGameObject->GetCamera());
		if (pFindIt != s_vCameras.end())
			s_vCameras.erase(pFindIt);
	}

	if (pGameObject->GetLight())
	{
		auto pFindIt = std::find(s_vLights.begin(), s_vLights.end(), pGameObject->GetLight());
		if (pFindIt != s_vLights.end())
			s_vLights.erase(pFindIt);
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
	m_tCameraShakeTimer.SetEndTime(fMaxTime);
	m_tCameraShakeTimer.Start();
	m_vCameraShakeImpulse = vImpulse;
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

weak_ptr<ComponentObject> Scene::GetBGCamera()
{
	assert(!s_vCameras.empty());
	weak_ptr<Camera> pBGCamera = s_vCameras[2];
	return static_pointer_cast<ComponentObject>(pBGCamera.lock()->GetGameObject());
}

weak_ptr<Player> Scene::GetPlayer()
{
	auto& vGameObjects = GetGameObjects(LAYER_TYPE::PLAYER);
	assert(!vGameObjects.empty());
	return static_pointer_cast<Player>(vGameObjects[0]);
}

void Scene::Load(const wstring& szPath)
{
	std::wifstream ifs(szPath, std::ios::in);

	uint32 iBGCount = 0;

	ifs >> iBGCount;
	//assert(iBGCount);

	for (uint32 i = 0; i < iBGCount; ++i)
	{
		wstring szTexPath = {};
		Vec3 vBGPosition = {};
		Vec3 vBGScale = {};

		ifs >> szTexPath;
		ifs.ignore(1);
		ifs >> vBGPosition.x >> vBGPosition.y >> vBGPosition.z;
		ifs.ignore(1);
		ifs >> vBGScale.x >> vBGScale.y >> vBGScale.z;
		ifs.ignore(1);

		shared_ptr<Background> pBackground = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(L"Deferred", szTexPath);
		pBackground->GetTransform()->SetLocalPosition(vBGPosition);
		pBackground->GetTransform()->SetLocalScale(vBGScale);

		pBackground->SetFrustum(false);
		pBackground->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pBackground, m_eSceneType));
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
		Vec2 vTileAlignVec;

		ifs >> szTexPath;
		ifs.ignore(1);
		ifs >> vTileAlignVec.x >> vTileAlignVec.y;
		ifs.ignore(1);

		shared_ptr<Tile> pTile= GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<Tile>(
			L"Deferred",
			false,
			ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 50.f), MassProperties(100.f, 100.f, 0.01f),
			szTexPath);

		pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
		pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

		// 잠들어 있는 Component 깨우기
		pTile->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));
	}

	uint32 iGateCount = 0;
	ifs >> iGateCount;

	for (uint32 i = 0; i < iGateCount; ++i)
	{
		uint32 iDungeonObjTypeEnum = 0;
		uint32 iStageKindEnum = 0;
		uint32 iDungeonTypeEnum = 0;

		wstring szTexPath = {};
		Vec2 vGatePos = {};

		ifs >> iDungeonObjTypeEnum;
		ifs.ignore(1);

		ifs >> iStageKindEnum;
		ifs.ignore(1);

		ifs >> iDungeonTypeEnum;
		ifs.ignore(1);

		ifs >> szTexPath;
		ifs.ignore(1);

		ifs >> vGatePos.x >> vGatePos.y;
		ifs.ignore(1);


		STAGE_KIND eStageKind = static_cast<STAGE_KIND>(iStageKindEnum);
		DUNGEON_TYPE eDungeonType = static_cast<DUNGEON_TYPE>(iDungeonTypeEnum);

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
				break;
			case DUNGEON_TYPE::DUNGEON_GOLD:
				break;
			case DUNGEON_TYPE::DUNGEON_BONE:
				break;
			case DUNGEON_TYPE::VICE_BOSS:
				break;
			case DUNGEON_TYPE::STAGE_BOSS:
				break;
			case DUNGEON_TYPE::SHOP:
				pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"DungeonGate_Shop_Activate", L"..\\Resources\\Animation\\Dungeon\\DungeonGate\\Shop\\dungeongate_shop_activate.anim");
				pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"DungeonGate_Shop_Deactivate", L"..\\Resources\\Animation\\Dungeon\\DungeonGate\\Shop\\dungeongate_shop_deactivate.anim");
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
			case DUNGEON_TYPE::SHOP:
				break;
			}
		}

		assert(pActivateAnimation && pDeactivateAnimation);

		pGameObject->AddComponent(make_shared<Animator>());
		pGameObject->GetAnimator()->AddAnimation(L"DungeonGate_Activate", pActivateAnimation);
		pGameObject->GetAnimator()->AddAnimation(L"DungeonGate_Deactivate", pDeactivateAnimation);
		pGameObject->GetAnimator()->Play(L"DungeonGate_Activate");

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTexPath, szTexPath);
		pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		pGameObject->GetTransform()->SetLocalPosition(Vec3(vGatePos.x, vGatePos.y, 100.f));

		pGameObject->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, m_eSceneType));
	}

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
