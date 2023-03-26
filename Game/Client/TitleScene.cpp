#include "pch.h"
#include "TitleScene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraMoveScript.h"
#include "Engine.h"
#include "Resources.h"
#include "Controller.h"
#include "PlayerMoveScript.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Physical.h"
#include "Player.h"
#include "EventManager.h"
#include "Input.h"
#include "SceneChangeEvent.h"
#include "UI.h"
#include "CameraFadeInOutScript.h"
#include "ObjectFadeInOutScript.h"


TitleScene::TitleScene()
	: Scene(SCENE_TYPE::TITLE)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Awake()
{
	Scene::Awake();
}

void TitleScene::Start()
{
	Scene::Start();
}

void TitleScene::Update()
{
	if (IS_DOWN(KEY_TYPE::N))
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<SceneChangeEvent>(SCENE_TYPE::TOWN));
	}

	Scene::Update();
}

void TitleScene::LateUpdate()
{
	Scene::LateUpdate();
}

void TitleScene::FinalUpdate()
{
	Scene::FinalUpdate();
}

void TitleScene::Render()
{
	Scene::Render();
}

void TitleScene::Enter()
{
	// Background
	{
		m_pBackground = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Title\\Image_TitleBG.tga");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		pMaterial->SetTexture(0, pTexture);
	
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		m_pBackground->AddComponent(pMeshRenderer);
		m_pBackground->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pBackground->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 100.f));
		m_pBackground->GetTransform()->SetLocalScale(Vec3(900.f, 450.f, 1.f));

		AddGameObject(m_pBackground);
	}

	// Logo
	{
		m_pLogo = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Title\\Image_TitleLogo.tga");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		m_pLogo->AddComponent(pMeshRenderer);
		m_pLogo->AddComponent(make_shared<Transform>());
		m_pLogo->AddComponent(make_shared<ObjectFadeInOutScript>(1.f, FADE_TYPE::FADE_IN, 1.5f));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pLogo->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 150.f, 90.f));
		m_pLogo->GetTransform()->SetLocalScale(pTexture->GetTexSize() * 2.f / 3.f);

		AddGameObject(m_pLogo);
	}

	// Camera
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);
	}

	// UI Camera
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->EnableAllCullingMask();
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::UI, false);
	}

	// Fade In / Out Object
	{
		shared_ptr<UI> pUI = make_shared<UI>();

		pUI->AddComponent(make_shared<Transform>());

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"FadeInOut");

		auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndicesTri(Vec3(1.f, 1.f, 1.f));
		shared_ptr<Mesh> pMesh = make_shared<Mesh>();

		pMesh->Init(vVertices, vIndices);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pUI->AddComponent(pMeshRenderer);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pUI->AddComponent(make_shared<CameraFadeInOutScript>(m_vCameras[1]));

		pUI->GetTransform()->SetLocalScale(Vec3(1600.f, 900.f, 50.f));
		pUI->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));

		AddGameObject(pUI);
	}
	m_vCameras[1]->SetCameraEffect(CAMERA_EFFECT::FADE_IN);
	// GameObject를 깨우는 작업
	Awake();
}

void TitleScene::Exit()
{
}
