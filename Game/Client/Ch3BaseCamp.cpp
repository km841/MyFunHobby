#include "pch.h"
#include "Ch3BaseCamp.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Ch3BeginTower.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"

Ch3BaseCamp::Ch3BaseCamp(const wstring& szMapPath)
	: BaseCamp(szMapPath)
{
}

Ch3BaseCamp::~Ch3BaseCamp()
{
}

void Ch3BaseCamp::Awake()
{
	BaseCamp::Awake();
}

void Ch3BaseCamp::Start()
{
	BaseCamp::Start();
}

void Ch3BaseCamp::Update()
{
	BaseCamp::Update();
}

void Ch3BaseCamp::LateUpdate()
{
	BaseCamp::LateUpdate();
}

void Ch3BaseCamp::FinalUpdate()
{
	BaseCamp::FinalUpdate();
}

void Ch3BaseCamp::Enter()
{
	BaseCamp::Enter();

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	// Ch3 Begin Tower
	{
		shared_ptr<Ch3BeginTower> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Ch3BeginTower>(
			L"Deferred", L"..\\Resources\\Texture\\DecoObject\\Image_Ch3BeginTower.png");

		pGameObject->GetTransform()->SetLocalPosition(Vec3(-1400.f, fHeight / 2.f + 65.f, 110.f));
		//pGameObject->GetTransform()->SetLocalScale(Vec3(134.f, 363.f, 1.f));

		pGameObject->Awake();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));
	}
}

void Ch3BaseCamp::Exit()
{
	BaseCamp::Exit();
}
