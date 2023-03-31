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
#include "Timer.h"
#include "Tile.h"
#include "PhysicsProperties.h"
#include "Physical.h"
#include "Collider.h"
#include "DebugRenderer.h"

ToolScene::ToolScene()
	: Scene(SCENE_TYPE::TOOL)
	, m_TileDragHolder(0.1f)
	, m_TileMapData{}
{
	m_TileDragHolder.Start();
}

ToolScene::~ToolScene()
{
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
	//PalleteUpdate();
	AnimationEditorUpdate();

	Scene::Update();
	UTILITY->ToolUpdate();

	if (IS_DOWN(KEY_TYPE::G))
		m_pGrid->FlipState();
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

	// Camera
	{
		m_pMainCamera = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		m_pMainCamera->AddComponent(make_shared<Transform>());
		m_pMainCamera->AddComponent(make_shared<Camera>());
		m_pMainCamera->AddComponent(make_shared<CameraMoveScript>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pMainCamera->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		m_pMainCamera->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(m_pMainCamera);
	}

	// Grid
	{
		m_pGrid = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

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
		CreateTile(vTilePos, m_TileMapData.vTileData[i].szTexPath);
	}
}

void ToolScene::EraseTileMap()
{
	for (auto& tile : m_mTileMap)
	{
		Vec3 vTilePos = Vec3(tile.first.x, tile.first.y, 1.f);
		EraseTile(vTilePos);
	}
}

void ToolScene::PalleteUpdate()
{
	m_TileDragHolder.Update(DELTA_TIME);

	m_TileMapData.vTileData.clear();

	auto& vTileGroup = m_vSceneObjects[static_cast<uint8>(LAYER_TYPE::TILE)];

	for (auto& pTile : vTileGroup)
	{
		shared_ptr<Material> pMaterial = pTile->GetMeshRenderer()->GetMaterial();
		wstring szTexPath = pMaterial->GetTexture(0)->GetName();
		Vec3 vPos = pTile->GetTransform()->GetLocalPosition();

		m_TileMapData.vTileData.push_back(TileData(szTexPath, ImVec2(vPos.x, vPos.y)));	
	}

	m_TileMapData.iTileCount = static_cast<uint32>(m_TileMapData.vTileData.size());

	if (TILEMAP_TOOL->IsTileSynced())
	{
		UTILITY->GetTool()->GetPallete()->SetTileMapData(m_TileMapData);
	}

	if (TILEMAP_TOOL->IsTileSend())
	{
		m_TileMapData = TILEMAP_TOOL->GetTileMapData();
		EraseTileMap();
		LoadTileMap();
		TILEMAP_TOOL->DisableIsTileSend();
		TILEMAP_TOOL->EnableTileSync();
	}
		
	wstring szSelectedKey = UTILITY->GetSelectedTileKey();

	const POINT& vMousePos = GET_SINGLE(Input)->GetMousePos();
	Vec3 vPosition = Vec3(static_cast<float>(vMousePos.x), static_cast<float>(vMousePos.y), 100.f);
	Vec3 vWorldPos = GET_SINGLE(Scenes)->ScreenToWorldPosition(vPosition, m_pMainCamera->GetCamera());

	if (L"FAILURE" != szSelectedKey)
	{
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(szSelectedKey);
		m_pPreviewTile->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		m_pPreviewTile->GetTransform()->SetLocalPosition(vWorldPos);
	}

	if (!IS_UP(KEY_TYPE::LBUTTON) && TILEMAP_TOOL->IsMouseNotOver())
	{ 
		DRAWING_TYPE eDrawingType = static_cast<DRAWING_TYPE>(TILEMAP_TOOL->GetDrawingType());
		OUTPUT_TYPE  eOutputType = static_cast<OUTPUT_TYPE>(TILEMAP_TOOL->GetOutputType());

		if (OUTPUT_TYPE::WRITE == eOutputType && (L"FAILURE" != szSelectedKey))
		{
			if ((DRAWING_TYPE::DRAGGING == eDrawingType) && IS_PRESS(KEY_TYPE::LBUTTON))
			{
				if (!CheckTileAtClick(vWorldPos) && m_TileDragHolder.IsFinished())
				{
					CreateTile(vWorldPos);
					m_TileDragHolder.Start();
				}
			}

			else if ((DRAWING_TYPE::POINT == eDrawingType) && IS_DOWN(KEY_TYPE::LBUTTON))
			{
				if (!CheckTileAtClick(vWorldPos))
					CreateTile(vWorldPos);
			}
		}

		else if (OUTPUT_TYPE::ERASE == eOutputType)
		{
			if ((DRAWING_TYPE::DRAGGING == eDrawingType) && IS_PRESS(KEY_TYPE::LBUTTON))
			{
				if (m_TileDragHolder.IsFinished())
				{
					EraseTile(vWorldPos);
					m_TileDragHolder.Start();
				}
			}

			else if ((DRAWING_TYPE::POINT == eDrawingType) && IS_DOWN(KEY_TYPE::LBUTTON))
			{
				EraseTile(vWorldPos);
			}
		}
	}
	

	if (IS_PRESS(KEY_TYPE::RBUTTON))
	{
		TILEMAP_TOOL->ClearClickedTile();
		m_pPreviewTile->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
	}
}

void ToolScene::CreateTile(const Vec3& vWorldPos)
{
	Vec2 vTileAlignVec = Conv::Vec3ToTileAlignVec2(vWorldPos);

	shared_ptr<Tile> pTile = Tile::Get();

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = m_pPreviewTile->GetMeshRenderer()->GetMaterial()->Clone();
	shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Forward");
	pMaterial->SetShader(pShader);
	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	pTile->AddComponent(pMeshRenderer);
	pTile->AddComponent(make_shared<Transform>());
	pTile->AddComponent(make_shared<Physical>(ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f)));
	pTile->AddComponent(make_shared<Collider>());
	pTile->AddComponent(make_shared<DebugRenderer>());

	pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
	pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

	// 잠들어 있는 Component 깨우기
	pTile->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));

	m_mTileMap[vTileAlignVec] = true;
}

void ToolScene::CreateTile(const Vec2& vTileAlignVec, wstring szTexPath)
{
	shared_ptr<Tile> pTile = Tile::Get();

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = make_shared<Material>();
	shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Forward");
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
	pTile->AddComponent(make_shared<DebugRenderer>());

	pTile->GetTransform()->SetLocalScale(Vec3(TILE_HALF_SIZE, TILE_HALF_SIZE, 1.f));
	pTile->GetTransform()->SetLocalPosition(Vec3(vTileAlignVec.x, vTileAlignVec.y, 100.f));

	// 잠들어 있는 Component 깨우기
	pTile->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));

	m_mTileMap[vTileAlignVec] = true;
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

			wstring szPath = Conv::AbsolutePathToRelativePath(ANIMATION_TOOL->GetSpriteTexturePath());
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
	// Bool값을 통해 툴의 상태를 확인하고 true라면 정보를 받아온다
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
