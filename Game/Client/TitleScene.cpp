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
#include "ObjectFactory.h"


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
		GET_SINGLE(EventManager)->AddEvent(make_unique<SceneChangeEvent>(SCENE_TYPE::TOOL));
	}

	if (m_tStayTimer.IsRunning())
		m_tStayTimer.Update(DELTA_TIME);

	if (m_tStayTimer.IsFinished())
	{
		m_fAlphaValue += DELTA_TIME;
		FONT->DrawString(L"�ƹ� Ű�� ��������", 22.f, Vec3(810.f, 60.f, 0.f), 
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
		m_pBackground = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(L"Deferred", L"..\\Resources\\Texture\\Title\\Image_TitleBG.png");
		m_pBackground->SetFrustum(false);

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pBackground->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 1000.f));
		m_pBackground->GetTransform()->SetLocalScale(Vec3(800.f, 450.f, 1.f));

		AddGameObject(m_pBackground);
	}

	// Logo
	{
		m_pLogo = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Background>(L"Forward", L"..\\Resources\\Texture\\Title\\Image_TitleLogo.png");
		m_pLogo->SetFrustum(false);
		m_pLogo->AddComponent(make_shared<ObjectFadeInOutScript>(1.f, FADE_TYPE::FADE_IN, 1.f));

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		m_pLogo->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 180.f, 900.f));
		Vec3 vTexSize = m_pLogo->GetMeshRenderer()->GetMaterial()->GetTexture(0)->GetTexSize() / 3.f;
		m_pLogo->GetTransform()->SetLocalScale(vTexSize);

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

	// GameObject�� ����� �۾�
	Awake();
}

void TitleScene::Exit()
{
}
