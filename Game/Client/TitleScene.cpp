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
#include "PlayerMoveScript.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Physical.h"
#include "Player.h"
#include "EventManager.h"
#include "Input.h"
#include "SceneChangeEvent.h"
#include "UI.h"
#include "ObjectFadeInOutScript.h"
#include "Light.h"
#include "SceneFadeEvent.h"
#include "ComponentObject.h"
#include "Clock.h"
#include "Background.h"


TitleScene::TitleScene()
	: Scene(SCENE_TYPE::TITLE)
	, m_fAlphaValue(-1.f)
	, m_tStayTimer(2.f)
{
	m_tStayTimer.Start();
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

	if (m_tStayTimer.IsRunning())
		m_tStayTimer.Update(DELTA_TIME);

	if (m_tStayTimer.IsFinished())
	{
		m_fAlphaValue += DELTA_TIME;
		FONT->DrawString(L"아무 키나 누르세요", 22.f, Vec3(810.f, 60.f, 0.f), 
			FONT_WEIGHT::ULTRA_BOLD, Color::FromRGB(203, 138, 241, (sinf(m_fAlphaValue) + 1.f) / 2.f));
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
	// Light
	{
		shared_ptr<ComponentObject> pGameObject = make_shared<ComponentObject>();
		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Light>());
		pGameObject->GetLight()->SetLightDirection(Vec3(0.f, 0.f, 1.f));
		pGameObject->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		pGameObject->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
		pGameObject->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		pGameObject->GetLight()->SetSpecular(Vec3(0.2f, 0.2f, 0.2f));

		AddGameObject(pGameObject);
	}

	// Background
	{
		m_pBackground = make_shared<Background>();
		m_pBackground->SetFrustum(false);

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Title\\Image_TitleBG.png");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		pMaterial->SetTexture(0, pTexture);
	
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		m_pBackground->AddComponent(pMeshRenderer);
		m_pBackground->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pBackground->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1000.f));
		m_pBackground->GetTransform()->SetLocalScale(Vec3(800.f, 450.f, 1.f));

		AddGameObject(m_pBackground);
	}

	// Logo
	{
		m_pLogo = make_shared<Background>();
		m_pLogo->SetFrustum(false);

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Title\\Image_TitleLogo.png");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		pMaterial->SetTexture(0, pTexture);

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		m_pLogo->AddComponent(pMeshRenderer);
		m_pLogo->AddComponent(make_shared<Transform>());
		m_pLogo->AddComponent(make_shared<ObjectFadeInOutScript>(1.f, FADE_TYPE::FADE_IN, 1.f));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pLogo->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 180.f, 900.f));
		m_pLogo->GetTransform()->SetLocalScale(pTexture->GetTexSize() / 3.f);

		AddGameObject(m_pLogo);
	}

	// Camera
	{
		shared_ptr<ComponentObject> pGameObject = make_shared<ComponentObject>();

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());
		

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::HUD, true);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::UI, true);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::INTERFACE_EFFECT, true);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::BACKGROUND, true);
	}


	// UI Camera
	{
		shared_ptr<ComponentObject> pGameObject = make_shared<ComponentObject>();

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->EnableAllCullingMask();
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::HUD, false);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::UI, false);
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::INTERFACE_EFFECT, false);
	}

	// Background Camera
	{
		shared_ptr<ComponentObject> pGameObject = make_shared<ComponentObject>();

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->GetCamera()->SetProjectionType(PROJECTION_TYPE::PERSPECTIVE);
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);

		pGameObject->GetCamera()->EnableAllCullingMask();
		pGameObject->GetCamera()->SetCullingMask(LAYER_TYPE::BACKGROUND, false);
	}

	RegisterSceneEvent(EVENT_TYPE::SCENE_FADE_EVENT, static_cast<uint8>(SCENE_FADE_EFFECT::FADE_IN), 1.f);

	// GameObject를 깨우는 작업
	Awake();
}

void TitleScene::Exit()
{
}
