#include "pch.h"
#include "BaseCamp.h"
#include "Engine.h"
#include "EventManager.h"
#include "ObjectFactory.h"
#include "JuniorKnight.h"

BaseCamp::BaseCamp(const wstring& szMapPath)
	: Dungeon(DUNGEON_TYPE::BASE_CAMP, szMapPath)
{
}

BaseCamp::~BaseCamp()
{
}

void BaseCamp::Awake()
{
	Dungeon::Awake();
}

void BaseCamp::Start()
{
	Dungeon::Start();
}

void BaseCamp::Update()
{
	Dungeon::Update();
}

void BaseCamp::LateUpdate()
{
	Dungeon::LateUpdate();
}

void BaseCamp::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void BaseCamp::Enter()
{
	GET_SINGLE(Scenes)->GetActiveScene()->Load(m_szMapPath);

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	// Create Monster
	{
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f - 600.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f - 300.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 300.f, fHeight / 2.f - 200.f, 99.5f));
		GET_SINGLE(ObjectFactory)->CreateMonsterAndAddedScene<JuniorKnight>(Vec3(fWidth / 2.f + 600.f, fHeight / 2.f - 200.f, 99.5f));
	}

	//Background
	{
		shared_ptr<GameObject> pGameObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
		pGameObject->SetFrustum(false);
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Texture> pTexture = make_shared<Texture>();
		pTexture->Load(L"..\\Resources\\Texture\\Map\\Image_BaseCamp_Background.png");
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		pMaterial->SetTexture(0, pTexture);
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pGameObject->AddComponent(pMeshRenderer);
		pGameObject->AddComponent(make_shared<Transform>());

		pGameObject->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f - 300.f, 140.f));
		pGameObject->GetTransform()->SetLocalScale(Vec3(1600.f, 900.f, 1.f));

		GET_SINGLE(Scenes)->GetActiveScene()->AddGameObject(pGameObject);
	}
}

void BaseCamp::Exit()
{
}
