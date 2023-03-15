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
#include "GridDrawScript.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"

#include "Tile.h"

ToolScene::ToolScene()
	: Scene(SCENE_TYPE::TOOL)
{
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
	PalleteUpdate();

	Scene::Update();
	UTILITY->ToolUpdate();
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
		m_pPreviewTile = GameObject::Get();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Preview");
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		m_pPreviewTile->AddComponent(pMeshRenderer);
		m_pPreviewTile->AddComponent(make_shared<Transform>());

		m_pPreviewTile->GetTransform()->SetLocalScale(Vec3(0.03f, 0.03f, 1.f));
		m_pPreviewTile->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 1.f));
		

		AddGameObject(m_pPreviewTile);
	}

	// Camera
	{
		m_pMainCamera = GameObject::Get();

		m_pMainCamera->AddComponent(make_shared<Transform>());
		m_pMainCamera->AddComponent(make_shared<Camera>());
		m_pMainCamera->AddComponent(make_shared<CameraMoveScript>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pMainCamera->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 0.f));
		m_pMainCamera->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(m_pMainCamera);
	}

	// Grid
	{
		m_pGrid = GameObject::Get();

		m_pGrid->AddComponent(make_shared<Transform>());
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Grid");
		pMeshRenderer->SetMaterial(pMaterial);

		auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndicesTri(Vec3(300.f, 300.f, 1.f));
		shared_ptr<Mesh> pMesh = make_shared<Mesh>();
		pMesh->Init(vVertices, vIndices);
		pMeshRenderer->SetMesh(pMesh);

		m_pGrid->AddComponent(pMeshRenderer);
		m_pGrid->AddComponent(make_shared<GridDrawScript>(m_pMainCamera->GetCamera()));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pGrid->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		m_pGrid->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(m_pGrid);
	}
}

void ToolScene::Exit()
{

}

void ToolScene::PalleteUpdate()
{
	wstring szSelectedKey = UTILITY->GetSelectedTileKey();
	if (L"FAILURE" != szSelectedKey)
	{
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(szSelectedKey);
		m_pPreviewTile->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);

		const POINT& vMousePos = GET_SINGLE(Input)->GetMousePos();
		Vec3 vPosition = Vec3(static_cast<float>(vMousePos.x), static_cast<float>(vMousePos.y), 1.f);
		Vec3 vWorldPos = GET_SINGLE(Scenes)->ScreenToWorldPosition(vPosition, m_pMainCamera->GetCamera());

		m_pPreviewTile->GetTransform()->SetLocalPosition(vWorldPos);


		// 클릭 이벤트에 대한 처리
		if (false == UTILITY->GetTool()->GetPallete()->IsMouseHovered())
		{
			DRAWING_TYPE eDrawingType = static_cast<DRAWING_TYPE>(UTILITY->GetTool()->GetPallete()->GetDrawingType());

			if ((DRAWING_TYPE::DRAGGING == eDrawingType) && IS_PRESS(KEY_TYPE::LBUTTON))
				CreateTile(vWorldPos);

			else if ((DRAWING_TYPE::POINT == eDrawingType) && IS_DOWN(KEY_TYPE::LBUTTON))
				CreateTile(vWorldPos);
		}
	}

	if (IS_PRESS(KEY_TYPE::RBUTTON))
	{
		UTILITY->GetTool()->GetPallete()->ClearClickedTile();
		m_pPreviewTile->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
	}
}

void ToolScene::CreateTile(Vec3 vWorldPos)
{
	shared_ptr<Tile> pTile = Tile::Get();

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = m_pPreviewTile->GetMeshRenderer()->GetMaterial()->Clone();
	shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(L"Alpha");
	pMaterial->SetShader(pShader);
	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	pTile->AddComponent(pMeshRenderer);
	pTile->AddComponent(make_shared<Transform>());

	pTile->GetTransform()->SetLocalScale(Vec3(0.03f, 0.03f, 1.f));
	pTile->GetTransform()->SetLocalPosition(vWorldPos);

	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pTile, m_eSceneType));
}
