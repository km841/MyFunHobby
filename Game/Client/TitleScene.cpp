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

#include "FadeInOutScript.h"

TitleScene::TitleScene()
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
		GET_SINGLE(EventManager)->AddEvent(make_unique<SceneChangeEvent>(SCENE_TYPE::TOOL));
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
		shared_ptr<GameObject> pGameObject = GameObject::Get();

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Image_Title.png");

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");
		pMaterial->SetTexture(0, pTexture);
	
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 25.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(19.f, 12.f, 1.f));

		AddGameObject(pGameObject);
	}

	// Camera
	{
		shared_ptr<GameObject> pGameObject = GameObject::Get();

		pGameObject->AddComponent(make_shared<Transform>());
		pGameObject->AddComponent(make_shared<Camera>());
		pGameObject->AddComponent(make_shared<CameraMoveScript>());

		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f, 0.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));
		AddGameObject(pGameObject);
	}

	// GameObject�� ����� �۾�
	Awake();

	//MessageBox(NULL, L"N Ű�� ������ ���� �ѱ� �� �ֽ��ϴ�", L"Message", MB_OK);
}

void TitleScene::Exit()
{
}
