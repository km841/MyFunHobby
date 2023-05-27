#include "pch.h"
#include "ToolScene.h"
#include "Engine.h"
#include "Transform.h"
#include "Material.h"
#include "Shader.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Utility.h"
#include "Texture.h"
#include "Input.h"
#include "Scenes.h"
#include "Camera.h"
#include "CameraMoveScript.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "Animator.h"
#include "Animation.h"
#include "Clock.h"
#include "Tile.h"
#include "PhysicsProperties.h"
#include "Physical.h"
#include "Collider.h"
#include "DebugRenderer.h"
#include "RigidBody.h"
#include "Light.h"
#include "Background.h"
#include "ObjectFactory.h"
#include "ComponentObject.h"
#include "DungeonGate.h"
#include "DungeonWall.h"
#include "DecoObject.h"
#include "LightObject.h"

ToolScene::ToolScene()
	: Scene(SCENE_TYPE::TOOL)
	, m_tTileDragHolder(0.1f)
	, m_TileMapData{}
	, m_bShowMousePos(false)
	, m_bTileAlignMode(false)
{
	m_tTileDragHolder.Start();
}

ToolScene::~ToolScene()
{
	m_vBackgrounds.clear();
}

void ToolScene::Awake()
{
	Scene::Awake();
}

void ToolScene::Start()
{
	Scene::Start();
}

void ToolScene::Update()
{
	MapEditorUpdate();
	//AnimationEditorUpdate();

	Scene::Update();
	UTILITY->ToolUpdate();

	POINT vMousePos = GET_SINGLE(Input)->GetMousePos();
	shared_ptr<ComponentObject> pCamera = GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock();
	Vec3 vWorldPos = GET_SINGLE(Scenes)->ScreenToWorldPosition(
		Vec3(static_cast<float>(vMousePos.x), static_cast<float>(vMousePos.y), 10.f), pCamera->GetCamera());

	if (m_bShowMousePos)
	{
		wstring szWorldPosX = std::to_wstring(vWorldPos.x);
		wstring szWorldPosY = std::to_wstring(vWorldPos.y);
		vWorldPos.y -= 30.f;

		FONT->DrawStringAtWorldPos(L"X: " + szWorldPosX + L"\nY: " + szWorldPosY, 20.f, vWorldPos, FONT_WEIGHT::BOLD);
	}

	if (m_bTileAlignMode)
	{
		vWorldPos.y -= 30.f;
		FONT->DrawStringAtWorldPos(L"TileAlign..", 20.f, vWorldPos, FONT_WEIGHT::BOLD);
	}

	if (IS_DOWN(KEY_TYPE::G))
		m_pGrid->FlipState();

	if (IS_DOWN(KEY_TYPE::P))
		m_bShowMousePos = (m_bShowMousePos + 1) % 2;

	if (IS_DOWN(KEY_TYPE::T))
		m_bTileAlignMode = (m_bTileAlignMode + 1) % 2;
}

void ToolScene::LateUpdate()
{
	Scene::LateUpdate();
}

void ToolScene::FinalUpdate()
{
	Scene::FinalUpdate();
}

void ToolScene::Render()
{
	Scene::Render();
	UTILITY->ToolRender();
}

void ToolScene::Enter()
{
	// Preview Tile
	{
		m_pPreviewTile = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Preview");
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		m_pPreviewTile->AddComponent(pMeshRenderer);
		m_pPreviewTile->AddComponent(make_shared<Transform>());
		m_pPreviewTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));

		AddGameObject(m_pPreviewTile);
	}

	// Animation Select Box
	for (int32 i = 0; i < FRAME_BOX_COUNT; ++i)
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndices(Vec3(1.f, 1.f, 1.f));

		shared_ptr<Mesh> pMesh = make_shared<Mesh>();
		pMesh->Init(vVertices, vIndices);

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"FrameDivider");

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial->Clone());
		pMeshRenderer->SetMesh(pMesh);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 100.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));

		pGameObject->Disable();
		AddGameObject(pGameObject);
		m_vFrameDividers.push_back(pGameObject);
	}

	// Sprite Texture
	{
		m_pSpriteTexture = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Atlas");
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial->Clone());
		pMeshRenderer->SetMesh(pMesh);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pSpriteTexture->AddComponent(pMeshRenderer);
		m_pSpriteTexture->AddComponent(make_shared<Transform>());
		m_pSpriteTexture->AddComponent(make_shared<Animator>());
		m_pSpriteTexture->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 100.f));

		AddGameObject(m_pSpriteTexture);
	}


	// Grid
	{
		m_pGrid = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		m_pGrid->SetFrustum(false);

		m_pGrid->AddComponent(make_shared<Transform>());
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Grid", L"..\\Resources\\Texture\\Grid.tga");
		pMaterial->SetTexture(0, pTexture);
		pMeshRenderer->SetMaterial(pMaterial->Clone());

		auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndicesTri(Vec3(GRID_SIZE, GRID_SIZE, 1.f));
		shared_ptr<Mesh> pMesh = make_shared<Mesh>();
		pMesh->Init(vVertices, vIndices);
		pMeshRenderer->SetMesh(pMesh);

		m_pGrid->AddComponent(pMeshRenderer);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pGrid->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f + 2.f, fHeight / 2.f - 32.5f, 150.f));
		m_pGrid->GetTransform()->SetLocalScale(Vec3(3.2f, 3.2f, 1.f));
		AddGameObject(m_pGrid);
	}

	AwakeLocalObjects();
}

void ToolScene::Exit()
{

}

void ToolScene::LoadTileMap()
{
	uint32 iCount = m_TileMapData.iTileCount;
	for (uint32 i = 0; i < iCount; ++i)
	{
		Vec2 vTilePos = Conv::ImVec2ToVec2(m_TileMapData.vTileData[i].vTilePos);
		CreateTile(vTilePos, m_TileMapData.vTileData[i].szTexPath, m_TileMapData.vTileData[i].eTileType);
	}

	for (uint32 i = 0; i < m_TileMapData.vDOData.size(); ++i)
	{
		Vec3 vWorldPos = Vec3(m_TileMapData.vDOData[i].vDOPos.x, m_TileMapData.vDOData[i].vDOPos.y, 100.f);

		switch (m_TileMapData.vDOData[i].eDungeonObjType)
		{
		case DUNGEON_OBJ_TYPE::DUNGEON_GATE:
			CreateDungeonGate(vWorldPos, m_TileMapData.vDOData[i].eStageKind, m_TileMapData.vDOData[i].eDungeonType, m_TileMapData.vDOData[i].szTexPath);
			break;

		case DUNGEON_OBJ_TYPE::DUNGEON_WALL:
			CreateDungeonWall(vWorldPos, m_TileMapData.vDOData[i].eStageKind);
			break;
		}
	}

	for (uint32 i = 0; i < m_TileMapData.vDecoData.size(); ++i)
	{
		Vec3 vWorldPos = Vec3(m_TileMapData.vDecoData[i].vDecoPos.x, m_TileMapData.vDecoData[i].vDecoPos.y, 100.f);

		switch (m_TileMapData.vDecoData[i].eDecoObjType)
		{
		case DECO_OBJECT_TYPE::NORMAL:
			CreateDecoObject(vWorldPos, m_TileMapData.vDecoData[i].szTexPath);
			break;
		}
	}

	for (uint32 i = 0; i < m_TileMapData.vLightData.size(); ++i)
	{
		CreateLightObject(m_TileMapData.vLightData[i]);
	}
}

void ToolScene::EraseTileMap()
{
	for (auto& tile : m_mTileMap)
	{
		Vec3 vTilePos = Vec3(tile.first.x, tile.first.y, 1.f);
		EraseTile(vTilePos);
	}

	auto& vDungeonGateObjects = GetGameObjects(LAYER_TYPE::DUNGEON_GATE);
	vDungeonGateObjects.clear();
}

void ToolScene::MapEditorUpdate()
{
	m_tTileDragHolder.Update(DELTA_TIME);

	m_TileMapData.vTileData.clear();
	m_TileMapData.vDOData.clear();
	m_TileMapData.vDecoData.clear();
	m_TileMapData.vLightData.clear();

	auto& vTileGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::TILE)];
	for (auto& pTile : vTileGroup)
	{
		shared_ptr<Material> pMaterial = pTile->GetMeshRenderer()->GetMaterial();
		wstring szTexPath = pMaterial->GetTexture(0)->GetName();
		Vec3 vPos = pTile->GetTransform()->GetLocalPosition();
		TILE_TYPE eTileType = static_pointer_cast<Tile>(pTile)->GetTileType();
		m_TileMapData.vTileData.push_back(TileData(eTileType, szTexPath, ImVec2(vPos.x, vPos.y)));
	}
	m_TileMapData.iTileCount = static_cast<uint32>(m_TileMapData.vTileData.size());

	auto& vDungeonGateGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::DUNGEON_GATE)];
	for (auto& pGate : vDungeonGateGroup)
	{
		shared_ptr<Material> pMaterial = pGate->GetMeshRenderer()->GetMaterial();
		wstring szTexPath = pMaterial->GetTexture(0)->GetName();
		Vec3 vPos = pGate->GetTransform()->GetLocalPosition();

		STAGE_KIND eStageKind = static_pointer_cast<DungeonGate>(pGate)->GetStageKind();
		DUNGEON_TYPE eDungeonType = static_pointer_cast<DungeonGate>(pGate)->GetDungeonType();
		m_TileMapData.vDOData.push_back(DungeonObjData{ DUNGEON_OBJ_TYPE::DUNGEON_GATE, eStageKind, eDungeonType, szTexPath, ImVec2(vPos.x, vPos.y) });
	}

	auto& vDungeonWallGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::DUNGEON_WALL)];
	for (auto& pWall : vDungeonWallGroup)
	{
		shared_ptr<Material> pMaterial = pWall->GetMeshRenderer()->GetMaterial();
		wstring szTexPath = pMaterial->GetTexture(0)->GetName();
		Vec3 vPos = pWall->GetTransform()->GetLocalPosition();

		STAGE_KIND eStageKind = static_pointer_cast<DungeonWall>(pWall)->GetStageKind();
		m_TileMapData.vDOData.push_back(DungeonObjData{ DUNGEON_OBJ_TYPE::DUNGEON_WALL, eStageKind, DUNGEON_TYPE::END, szTexPath, ImVec2(vPos.x, vPos.y) });
	}

	auto& vDecoObjectGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::DECO)];
	for (auto& pDeco : vDecoObjectGroup)
	{
		shared_ptr<Material> pMaterial = pDeco->GetMeshRenderer()->GetMaterial();
		wstring szTexPath = pMaterial->GetTexture(0)->GetName();
		Vec3 vPos = pDeco->GetTransform()->GetLocalPosition();

		DECO_OBJECT_TYPE eDecoType = static_pointer_cast<DecoObject>(pDeco)->GetDecoObjectType();
		m_TileMapData.vDecoData.push_back(DecoObjData{ eDecoType, szTexPath, ImVec2(vPos.x, vPos.y)});
	}

	auto& vLightObjectGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::LIGHT_OBJECT)];
	for (auto& pLightObject : vLightObjectGroup)
	{
		Vec3 vPos = pLightObject->GetTransform()->GetLocalPosition();
		shared_ptr<Light> pLight = pLightObject->GetLight();
		Vec3 vDiffuse = pLight->GetDiffuse();
		Vec3 vAmbient = pLight->GetAmbient();
		float fRange = pLight->GetRange();

		m_TileMapData.vLightData.push_back(LightData{ 
			Conv::Vec3ToImVec3(vDiffuse), Conv::Vec3ToImVec3(vAmbient), fRange, Conv::Vec3ToImVec3(vPos) });
	}

	if (MAP_TOOL->IsDataSynced())
	{
		MAP_TOOL->SetTileMapData(m_TileMapData);
	}

	if (MAP_TOOL->IsDataSend())
	{
		m_TileMapData = MAP_TOOL->GetTileMapData();
		EraseTileMap();
		LoadTileMap();

		m_vBackgroundDataList = MAP_TOOL->GetBackgroundDataList();
		EraseAllBackground();
		LoadBackgrounds();

		MAP_TOOL->DisableIsDataSend();
		MAP_TOOL->EnableDataSync();
	}
		
	wstring szSelectedKey = UTILITY->GetSelectedTileKey();

	const POINT& vMousePos = GET_SINGLE(Input)->GetMousePos();
	Vec3 vPosition = Vec3(static_cast<float>(vMousePos.x), static_cast<float>(vMousePos.y), 79.f);
	Vec3 vWorldPos = GET_SINGLE(Scenes)->ScreenToWorldPosition(vPosition, GetMainCamera().lock()->GetCamera());
	//Vec3 vScreenPos = GET_SINGLE(Scenes)->WorldToScreenPosition(vWorldPos, GetMainCamera().lock()->GetCamera());
	vWorldPos.x += TILE_HALF_SIZE;
	vWorldPos.y += 5.f;
	m_pPreviewTile->GetTransform()->SetLocalPosition(vWorldPos);

	if (L"FAILURE" != szSelectedKey)
	{
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(szSelectedKey);
		m_pPreviewTile->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		m_pPreviewTile->GetTransform()->SetLocalScale(pTexture->GetTexSize());
	}

	if (!IS_UP(KEY_TYPE::LBUTTON) && MAP_TOOL->IsMouseNotOver())
	{
		DRAWING_TYPE eDrawingType = static_cast<DRAWING_TYPE>(MAP_TOOL->GetDrawingType());
		OUTPUT_TYPE  eOutputType = static_cast<OUTPUT_TYPE>(MAP_TOOL->GetOutputType());
		TILE_TYPE eTileType = static_cast<TILE_TYPE>(MAP_TOOL->GetClickedColliderType());
		SRV_KIND eSRVKind = GetSelectedSRVKind(szSelectedKey);

		if (m_bTileAlignMode)
		{
			Vec2 vTileAlignVec2 = Conv::Vec3ToTileAlignVec2(vWorldPos);
			vWorldPos.x = vTileAlignVec2.x;
			vWorldPos.y = vTileAlignVec2.y;
		}


		if (OUTPUT_TYPE::WRITE == eOutputType && (L"FAILURE" != szSelectedKey))
		{
			if ((DRAWING_TYPE::DRAGGING == eDrawingType) && IS_PRESS(KEY_TYPE::LBUTTON))
			{
				if (m_tTileDragHolder.IsFinished())
				{
					if (SRV_KIND::TILE == eSRVKind && !CheckTileAtClick(vWorldPos))
					{
						CreateTile(vWorldPos, eTileType);
					}
					else
					{

						if (!m_bTileAlignMode)
						{
							switch (eSRVKind)
							{
							case SRV_KIND::DUNGEON_GATE:
								CreateDungeonGate(vWorldPos, szSelectedKey);
								break;
							case SRV_KIND::DUNGEON_WALL:
								CreateDungeonWall(vWorldPos, szSelectedKey);
								break;
							case SRV_KIND::DECO_OBJECT:
								CreateDecoObject(vWorldPos, szSelectedKey);
								break;
							}
						}
						else
						{
							if (!CheckTileAtClick(vWorldPos))
							{
								switch (eSRVKind)
								{
								case SRV_KIND::DUNGEON_GATE:
									CreateDungeonGate(vWorldPos, szSelectedKey);
									break;
								case SRV_KIND::DUNGEON_WALL:
									CreateDungeonWall(vWorldPos, szSelectedKey);
									break;
								case SRV_KIND::DECO_OBJECT:
									CreateDecoObject(vWorldPos, szSelectedKey);
									break;
								}
							}
						}

					}

					m_tTileDragHolder.Start();
				}
			}

			else if ((DRAWING_TYPE::POINT == eDrawingType) && IS_DOWN(KEY_TYPE::LBUTTON))
			{
				if (!m_bTileAlignMode)
				{
					switch (eSRVKind)
					{
					case SRV_KIND::DUNGEON_GATE:
						CreateDungeonGate(vWorldPos, szSelectedKey);
						break;
					case SRV_KIND::DUNGEON_WALL:
						CreateDungeonWall(vWorldPos, szSelectedKey);
						break;
					case SRV_KIND::DECO_OBJECT:
						CreateDecoObject(vWorldPos, szSelectedKey);
						break;
					}
				}
				else
				{
					if (!CheckTileAtClick(vWorldPos))
					{
						switch (eSRVKind)
						{
						case SRV_KIND::DUNGEON_GATE:
							CreateDungeonGate(vWorldPos, szSelectedKey);
							break;
						case SRV_KIND::DUNGEON_WALL:
							CreateDungeonWall(vWorldPos, szSelectedKey);
							break;
						case SRV_KIND::DECO_OBJECT:
							CreateDecoObject(vWorldPos, szSelectedKey);
							break;
						}
					}
				}

			}
		}

		else if (OUTPUT_TYPE::ERASE == eOutputType)
		{
			if ((DRAWING_TYPE::DRAGGING == eDrawingType) && IS_PRESS(KEY_TYPE::LBUTTON))
			{
				if (m_tTileDragHolder.IsFinished())
				{
					EraseTile(vWorldPos);
					m_tTileDragHolder.Start();
				}
			}

			else if ((DRAWING_TYPE::POINT == eDrawingType) && IS_DOWN(KEY_TYPE::LBUTTON))
			{
				EraseTile(vWorldPos);
			}
		}

		else if (MAP_TOOL->IsCreateLightFlag())
		{
			if (m_pPreviewTile->GetLight())
			{
				shared_ptr<Light> pLight = m_pPreviewTile->GetLight();
				auto iter = std::find(m_vLights.begin(), m_vLights.end(), pLight);
				if (iter != m_vLights.end())
					m_vLights.erase(iter);
				m_pPreviewTile->RemoveComponent(COMPONENT_TYPE::LIGHT);
			}

			LightData lightData = MAP_TOOL->GetLightData();
			m_pPreviewTile->AddComponent(make_shared<Light>());
			m_pPreviewTile->GetLight()->SetDiffuse(Conv::ImVec3ToVec3(lightData.vDiffuse));
			m_pPreviewTile->GetLight()->SetAmbient(Conv::ImVec3ToVec3(lightData.vAmbient));
			m_pPreviewTile->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
			m_pPreviewTile->GetLight()->SetLightRange(lightData.fRadius);
			m_vLights.push_back(m_pPreviewTile->GetLight());

			MAP_TOOL->DisableCreateLightFlag();
		}

		else if (m_pPreviewTile->GetLight() && IS_DOWN(KEY_TYPE::LBUTTON))
		{
			CreateLightObject(vWorldPos);
		}
	}

	if (MAP_TOOL->IsCreateBGFlag())
	{
		Vec3 vWorldPos = Conv::ImVec3ToVec3(MAP_TOOL->GetCreateBGPos());
		Vec3 vWorldScale = Conv::ImVec3ToVec3(MAP_TOOL->GetCreateBGScale());
		Vec3 vSpeed = Conv::ImVec3ToVec3(MAP_TOOL->GetCreateBGSpeed());
		const wstring& szBGImagePath = AbsolutePathToRelativePath(MAP_TOOL->GetBGImagePath());
		CreateBGAndAddedToScene(vWorldPos, vWorldScale, vSpeed, szBGImagePath);

		MAP_TOOL->DisableCreateBGFlag();
	}

	if (MAP_TOOL->IsChangedBGDataFlag())
	{
		const BackgroundData& backgroundData = MAP_TOOL->GetSelectedBGData();
		int32 iBackgroundIndex = MAP_TOOL->GetSelectedBGIndex();

		m_vBackgrounds[iBackgroundIndex]->GetTransform()->SetLocalPosition(Conv::ImVec3ToVec3(backgroundData.vBGPos));
		m_vBackgrounds[iBackgroundIndex]->GetTransform()->SetLocalScale(Conv::ImVec3ToVec3(backgroundData.vBGScale));
		m_vBackgrounds[iBackgroundIndex]->SetFollowSpeed(Conv::ImVec3ToVec3(backgroundData.vBGSpeed));

		MAP_TOOL->DisableChangedBGDataFlag();
	}

	if (MAP_TOOL->IsRemoveBGDataFlag())
	{
		int32 iBackgroundIndex = MAP_TOOL->GetSelectedBGIndex();

		auto& vGameObjects = GetGameObjects(LAYER_TYPE::BACKGROUND);

		auto iter = vGameObjects.begin() + iBackgroundIndex;
		iter->get()->Release();
		vGameObjects.erase(vGameObjects.begin() + iBackgroundIndex);
		m_vBackgrounds.erase(m_vBackgrounds.begin() + iBackgroundIndex);

		MAP_TOOL->DisableRemoveBGDataFlag();
	}
	

	if (IS_PRESS(KEY_TYPE::RBUTTON))
	{
		MAP_TOOL->ClearClickedTile();
		m_pPreviewTile->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);

		if (m_pPreviewTile->GetLight())
		{
			shared_ptr<Light> pLight = m_pPreviewTile->GetLight();
			auto iter = std::find(m_vLights.begin(), m_vLights.end(), pLight);
			if (iter != m_vLights.end())
				m_vLights.erase(iter);

			m_pPreviewTile->RemoveComponent(COMPONENT_TYPE::LIGHT);
		}
	}
}

void ToolScene::CreateTile(const Vec3& vWorldPos, TILE_TYPE eTileType)
{
	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	shared_ptr<Tile> pTile = Tile::Get();
	pTile->Init(static_cast<int32>(eTileType));

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = m_pPreviewTile->GetMeshRenderer()->GetMaterial()->Clone();
	shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Deferred");
	pMaterial->SetShader(pShader);
	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	pTile->AddComponent(pMeshRenderer);
	pTile->AddComponent(make_shared<Transform>());
	pTile->AddComponent(make_shared<Physical>(ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f)));
	pTile->AddComponent(make_shared<Collider>());
	pTile->AddComponent(make_shared<RigidBody>());
	pTile->AddComponent(make_shared<DebugRenderer>());

	pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
	pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

	// 잠들어 있는 Component 깨우기
	pTile->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));

	m_mTileMap[vTileAlignVec] = true;
}

void ToolScene::CreateTile(const Vec2& vTileAlignVec, wstring szTexPath, TILE_TYPE eTileType)
{
	shared_ptr<Tile> pTile = Tile::Get();
	pTile->Init(static_cast<int32>(eTileType));

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = make_shared<Material>();
	shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Deferred");
	pMaterial->SetShader(pShader);

	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTexPath, szTexPath);
	assert(pTexture);
	pMaterial->SetTexture(0, pTexture);

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	pTile->AddComponent(pMeshRenderer);
	pTile->AddComponent(make_shared<Transform>());
	pTile->AddComponent(make_shared<Physical>(ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f)));
	pTile->AddComponent(make_shared<Collider>());
	pTile->AddComponent(make_shared<RigidBody>());
	pTile->AddComponent(make_shared<DebugRenderer>());

	pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
	pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

	// 잠들어 있는 Component 깨우기
	pTile->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));

	m_mTileMap[vTileAlignVec] = true;
}

void ToolScene::CreateDungeonGate(const Vec3& vWorldPos, const wstring& szSelectedKey)
{
	DungeonObjPair eEnumPair = WstringToDungeonObjPair(szSelectedKey);
	STAGE_KIND eStageKind = eEnumPair.first;
	DUNGEON_TYPE eDungeonType = eEnumPair.second;
	CreateDungeonGate(vWorldPos, eStageKind, eDungeonType);
}

void ToolScene::CreateDungeonGate(const Vec3& vWorldPos, STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType, const wstring& szTexPath)
{
	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTexPath, szTexPath);
	Vec3 vTexSize = pTexture->GetTexSize();

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
			break;
		case DUNGEON_TYPE::DUNGEON_GOLD:
			break;
		case DUNGEON_TYPE::DUNGEON_BONE:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Bone_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Bone\\ch3dungeongate_bone_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Bone_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Bone\\ch3dungeongate_bone_deactivate.anim");
			break;
		case DUNGEON_TYPE::VICE_BOSS:
			break;
		case DUNGEON_TYPE::STAGE_BOSS:
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
	pGameObject->GetAnimator()->Play(L"DungeonGate_Activate");


	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	pGameObject->GetTransform()->SetLocalScale(Vec3(vTexSize.x, vTexSize.y, 1.f));
	pGameObject->GetTransform()->SetLocalPosition(Vec3(vWorldPos.x, vWorldPos.y, 100.f));

	pGameObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, m_eSceneType));
}

void ToolScene::CreateDungeonGate(const Vec3& vWorldPos, STAGE_KIND eStageKind, DUNGEON_TYPE eDungeonType)
{
	shared_ptr<Texture> pTexture = m_pPreviewTile->GetMeshRenderer()->GetMaterial()->GetTexture(0);
	Vec3 vTexSize = pTexture->GetTexSize();

	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	shared_ptr<DungeonGate> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DungeonGate>(
		L"Deferred", false, ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(vTexSize.x, vTexSize.y, 1.f), MassProperties(), L"", eStageKind, eDungeonType);

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
			break;
		case DUNGEON_TYPE::DUNGEON_GOLD:
			break;
		case DUNGEON_TYPE::DUNGEON_BONE:
			pActivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Bone_Activate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Bone\\ch3dungeongate_bone_activate.anim");
			pDeactivateAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Ch3DungeonGate_Bone_Deactivate", L"..\\Resources\\Animation\\Dungeon\\Ch3\\DungeonGate\\Bone\\ch3dungeongate_bone_deactivate.anim");
			break;
		case DUNGEON_TYPE::VICE_BOSS:
			break;
		case DUNGEON_TYPE::STAGE_BOSS:
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
	pGameObject->GetAnimator()->Play(L"DungeonGate_Activate");

	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	pGameObject->GetTransform()->SetLocalScale(Vec3(vTexSize.x, vTexSize.y, 1.f));
	pGameObject->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y + vTexSize.y - (TILE_HALF_SIZE + 10.f), 100.f));

	pGameObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, m_eSceneType));
}

void ToolScene::CreateDungeonWall(const Vec3& vWorldPos, const wstring& szSelectedKey)
{
	DungeonObjPair eEnumPair = WstringToDungeonObjPair(szSelectedKey);
	STAGE_KIND eStageKind = eEnumPair.first;

	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	shared_ptr<DungeonWall> pDungeonWall = nullptr;
	switch (eStageKind)
	{
	case STAGE_KIND::BLACK_LAB:
		pDungeonWall = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DungeonWall>(L"Deferred", L"..\\Resources\\Texture\\Sprites\\Dungeon\\Ch3\\DungeonWall\\Image_Ch3_Dungeon_Wall.png", eStageKind);
		break;
	case STAGE_KIND::CITADEL_OF_FATE:
		break;
	}
	assert(pDungeonWall);

	Vec3 vTexSize = pDungeonWall->GetMeshRenderer()->GetMaterial()->GetTexture(0)->GetTexSize();
	pDungeonWall->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y + vTexSize.y - 40.f, 102.f));

	pDungeonWall->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDungeonWall, m_eSceneType));
}

void ToolScene::CreateDungeonWall(const Vec3& vWorldPos, STAGE_KIND eStageKind)
{
	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	shared_ptr<DungeonWall> pDungeonWall = nullptr;
	switch (eStageKind)
	{
	case STAGE_KIND::BLACK_LAB:
		pDungeonWall = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<DungeonWall>(L"Deferred", L"..\\Resources\\Texture\\Sprites\\Dungeon\\Ch3\\DungeonWall\\Image_Ch3_Dungeon_Wall.png", eStageKind);
		break;
	case STAGE_KIND::CITADEL_OF_FATE:
		break;
	}
	assert(pDungeonWall);

	Vec3 vTexSize = pDungeonWall->GetMeshRenderer()->GetMaterial()->GetTexture(0)->GetTexSize();
	pDungeonWall->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 102.f));

	pDungeonWall->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDungeonWall, m_eSceneType));
}

void ToolScene::CreateDecoObject(const Vec3& vWorldPos, const wstring& szSelectedKey)
{
	shared_ptr<DecoObject> pDecoObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<DecoObject>(L"Deferred", szSelectedKey);
	pDecoObject->GetTransform()->SetLocalPosition(Vec3(vWorldPos.x, vWorldPos.y, 99.f));

	pDecoObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDecoObject, m_eSceneType));

	if (m_bTileAlignMode)
		m_mTileMap[Vec2(vWorldPos.x, vWorldPos.y)] = true;
}

void ToolScene::CreateLightObject(const Vec3& vWorldPos)
{
	shared_ptr<LightObject> pLightObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LightObject>(L"Deferred");
	pLightObject->GetTransform()->SetLocalPosition(Vec3(vWorldPos.x, vWorldPos.y, 95.f));

	pLightObject->AddComponent(make_shared<Light>());
	pLightObject->GetLight()->SetDiffuse(m_pPreviewTile->GetLight()->GetDiffuse());
	pLightObject->GetLight()->SetAmbient(m_pPreviewTile->GetLight()->GetAmbient());
	pLightObject->GetLight()->SetLightRange(m_pPreviewTile->GetLight()->GetRange());
	pLightObject->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	pLightObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLightObject, m_eSceneType));
}

void ToolScene::CreateLightObject(const LightData& lightData)
{
	Vec3 vWorldPos = Conv::ImVec3ToVec3(lightData.vLightPos);
	Vec3 vDiffuse = Conv::ImVec3ToVec3(lightData.vDiffuse);
	Vec3 vAmbient = Conv::ImVec3ToVec3(lightData.vAmbient);
	float fRadius = lightData.fRadius;

	shared_ptr<LightObject> pLightObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LightObject>(L"Deferred");
	pLightObject->GetTransform()->SetLocalPosition(Vec3(vWorldPos.x, vWorldPos.y, 100.f));

	pLightObject->AddComponent(make_shared<Light>());
	pLightObject->GetLight()->SetDiffuse(vDiffuse);
	pLightObject->GetLight()->SetAmbient(vAmbient);
	pLightObject->GetLight()->SetLightRange(fRadius);
	pLightObject->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);

	pLightObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLightObject, m_eSceneType));
}

void ToolScene::EraseTile(const Vec3& vWorldPos)
{
	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	auto& vTileGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::TILE)];

	for (auto iter = vTileGroup.begin(); iter != vTileGroup.end();)
	{
		const Vec3& vLocalPos = (*iter)->GetTransform()->GetLocalPosition();

		if (LAYER_TYPE::TILE == (*iter)->GetLayerType() && 
			(vLocalPos.x == vTileAlignVec.x) && (vLocalPos.y == vTileAlignVec.y))
		{
			Tile::Release(static_pointer_cast<Tile>(*iter));
			iter = vTileGroup.erase(iter);
			m_mTileMap[vTileAlignVec] = false;
			continue;
		}
		iter++;
	}
}

bool ToolScene::CheckTileAtClick(const Vec3& vWorldPos)
{
	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	auto iter = m_mTileMap.find(vTileAlignVec);
	if (m_mTileMap.end() == iter)
		return false;

	else
		return m_mTileMap[vTileAlignVec];
}

void ToolScene::CreateBGAndAddedToScene(const Vec3& vWorldPos, const Vec3& vWorldScale, const Vec3& vSpeed, const wstring& szBGImagePath)
{
	shared_ptr<Background> pBackground = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(L"Deferred", szBGImagePath);
	pBackground->SetFrustum(false);
	pBackground->GetTransform()->SetLocalPosition(vWorldPos);
	pBackground->GetTransform()->SetLocalScale(vWorldScale);
	pBackground->SetFollowSpeed(vSpeed);

	m_vBackgrounds.push_back(pBackground);
	AddGameObject(pBackground);
}

void ToolScene::EraseAllBackground()
{
	auto& vBackgrounds = GetGameObjects(LAYER_TYPE::BACKGROUND);
	vBackgrounds.clear();
}

void ToolScene::LoadBackgrounds()
{
	if (m_vBackgroundDataList.empty())
		return;

	for (int32 i = 0; i < m_vBackgroundDataList.size(); ++i)
	{
		const auto& szPath = m_vBackgroundDataList[i].szBGImagePath;
		Vec3 vPosition = Conv::ImVec3ToVec3(m_vBackgroundDataList[i].vBGPos);
		Vec3 vScale = Conv::ImVec3ToVec3(m_vBackgroundDataList[i].vBGScale);
		Vec3 vSpeed = Conv::ImVec3ToVec3(m_vBackgroundDataList[i].vBGSpeed);

		CreateBGAndAddedToScene(vPosition, vScale, vSpeed, szPath);
	}
}

SRV_KIND ToolScene::GetSelectedSRVKind(const wstring& szSRVKey)
{
	if (szSRVKey.find(L"Tiles") != std::wstring::npos)
		return SRV_KIND::TILE;
	else if (szSRVKey.find(L"Gate") != std::wstring::npos)
		return SRV_KIND::DUNGEON_GATE;
	else if (szSRVKey.find(L"Wall") != std::wstring::npos)
		return SRV_KIND::DUNGEON_WALL;
	else if (szSRVKey.find(L"Deco") != std::wstring::npos)
		return SRV_KIND::DECO_OBJECT;

	return SRV_KIND::END;
}

DungeonObjPair ToolScene::WstringToDungeonObjPair(const wstring& szSelectedKey)
{
	if (szSelectedKey.find(L"Ch3") != std::wstring::npos &&
		szSelectedKey.find(L"Item") != std::wstring::npos)
		return DungeonObjPair(STAGE_KIND::BLACK_LAB, DUNGEON_TYPE::DUNGEON_ITEM);

	else if (szSelectedKey.find(L"Ch4") != std::wstring::npos &&
		szSelectedKey.find(L"Item") != std::wstring::npos)
		return DungeonObjPair(STAGE_KIND::CITADEL_OF_FATE, DUNGEON_TYPE::DUNGEON_ITEM);

	else if (szSelectedKey.find(L"Ch3") != std::wstring::npos &&
		szSelectedKey.find(L"Bone") != std::wstring::npos)
		return DungeonObjPair(STAGE_KIND::BLACK_LAB, DUNGEON_TYPE::DUNGEON_BONE);

	else if (szSelectedKey.find(L"Ch4") != std::wstring::npos &&
		szSelectedKey.find(L"Bone") != std::wstring::npos)
		return DungeonObjPair(STAGE_KIND::CITADEL_OF_FATE, DUNGEON_TYPE::DUNGEON_BONE);

	else if (szSelectedKey.find(L"Ch3") != std::wstring::npos &&
		szSelectedKey.find(L"Wall") != std::wstring::npos)
		return DungeonObjPair(STAGE_KIND::BLACK_LAB, DUNGEON_TYPE::END);

	else if (szSelectedKey.find(L"Ch4") != std::wstring::npos &&
		szSelectedKey.find(L"Wall") != std::wstring::npos)
		return DungeonObjPair(STAGE_KIND::CITADEL_OF_FATE, DUNGEON_TYPE::END);

	return DungeonObjPair(STAGE_KIND::END, DUNGEON_TYPE::END);
}

void ToolScene::AnimationEditorUpdate()
{
	SpriteUpdate();
	DrawEditorGraphic();
	PlayAnimation();
}

void ToolScene::SpriteUpdate()
{
	if (ANIMATION_TOOL->IsSpriteUpdate())
	{
		const wstring& szSpriteTexPath = ANIMATION_TOOL->GetSpriteTexturePath();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szSpriteTexPath, szSpriteTexPath);
		assert(pTexture);
		m_pSpriteTexture->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		m_pSpriteTexture->GetTransform()->SetLocalScale(pTexture->GetTexSize());
		ANIMATION_TOOL->SpriteUpdateDisable();
	}
}

void ToolScene::DrawEditorGraphic()
{
	Vec2 vInputLT = Conv::ImVec2ToVec2(ANIMATION_TOOL->GetSpriteLTPoint());
	Vec2 vInputSize = Conv::ImVec2ToVec2(ANIMATION_TOOL->GetSpriteSize());
	Vec2 vInputOffset = Conv::ImVec2ToVec2(ANIMATION_TOOL->GetOffset());
	float fInputDuration = ANIMATION_TOOL->GetDuration();

	Vec3 vTextureSize = m_pSpriteTexture->GetTransform()->GetLocalScale();
	Vec3 vTexturePos = m_pSpriteTexture->GetTransform()->GetLocalPosition();

	float fLTPointX = vTexturePos.x - vTextureSize.x;
	float fLTPointY = vTexturePos.y + vTextureSize.y;

	float fCenterPointX = fLTPointX + vInputSize.x + (vInputLT.x * 2.f);
	float fCenterPointY = fLTPointY - vInputSize.y - (vInputLT.y * 2.f);

	if (0.f < vInputSize.x && 0.f < vInputSize.y)
	{
		int32 iSpriteCount = static_cast<int32>(vTextureSize.x / vInputSize.x);

		if (FRAME_BOX_COUNT - 1 < iSpriteCount)
			return;

		for (int32 i = 0; i < FRAME_BOX_COUNT - 1; ++i)
		{
			if (i < iSpriteCount)
			{
				if (m_pSpriteTexture->GetAnimator()->GetActiveAnimation())
				{
					m_vFrameDividers[i]->Disable();
					continue;
				}

				m_vFrameDividers[i]->Enable();
				m_vFrameDividers[i]->GetTransform()->SetLocalPosition(Vec3(fCenterPointX + ((vInputSize.x * 2.f) * i), fCenterPointY, 1.f));
				m_vFrameDividers[i]->GetTransform()->SetLocalScale(Vec3(vInputSize.x, vInputSize.y, 1.f));
			}

			else
			{
				m_vFrameDividers[i]->Disable();
			}
		}

		if (ANIMATION_TOOL->IsReadable())
		{
			ANIMATION_TOOL->ClearFrameDataList();

			wstring szPath = AbsolutePathToRelativePath(ANIMATION_TOOL->GetSpriteTexturePath());
			const wstring& szName = ANIMATION_TOOL->GetAnimationName();
			const  ImVec2& vSpriteSize = ANIMATION_TOOL->GetSpriteSize();
			const  ImVec2& vOffset = ANIMATION_TOOL->GetOffset();

			for (int32 i = 0; i < iSpriteCount; ++i)
			{
				FrameData frameData = {};
				frameData.szName = szName;
				frameData.szTexPath = szPath;
				frameData.iFrameCount = iSpriteCount;
				frameData.fDuration = fInputDuration;
				frameData.vLTPos = ImVec2(vInputLT.x + (vInputSize.x * i), vInputLT.y);
				frameData.vSize = vSpriteSize;
				frameData.vOffset = vOffset;

				ANIMATION_TOOL->InsertFrameData(frameData);	
			}

			ANIMATION_TOOL->FlipReadableFlag();
		}
	}
}

void ToolScene::PlayAnimation()
{
	if (ANIMATION_TOOL->GetAnimPlayingFlag())
	{
		const auto& vFrameDataList = ANIMATION_TOOL->GetFrameDataList();
		assert(!vFrameDataList.empty());
		
		if (!m_pSpriteTexture->GetAnimator()->GetActiveAnimation())
		{
			Vec3 vSpriteSize = Vec3(vFrameDataList[0].vSize.x, vFrameDataList[0].vSize.y, 1.f);
			m_pSpriteTexture->GetTransform()->SetLocalScale(vSpriteSize);
			m_pSpriteTexture->GetAnimator()->CreateAnimation(vFrameDataList);
			m_pSpriteTexture->GetAnimator()->Play(vFrameDataList[0].szName);
		}

		else
		{
			m_pSpriteTexture->GetAnimator()->GetActiveAnimation()->RefreshAnimation(vFrameDataList);
		}

		ANIMATION_TOOL->FlipAnimPlayingFlag();
	}
}
