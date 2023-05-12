#include "pch.h"
#include "Ch3BeginTower.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Light.h"

Ch3BeginTower::Ch3BeginTower()
{
}

Ch3BeginTower::~Ch3BeginTower()
{
}

void Ch3BeginTower::Awake()
{
	GameObject::Awake();
	CreateLightsAndAddedToScene();
}

void Ch3BeginTower::Start()
{
	GameObject::Start();
}

void Ch3BeginTower::Update()
{
	GameObject::Update();
}

void Ch3BeginTower::LateUpdate()
{
	GameObject::LateUpdate();
}

void Ch3BeginTower::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Ch3BeginTower::CreateLightsAndAddedToScene()
{
	for (int32 i = 0; i < 3; ++i)
	{
		for (int32 j = 0; j < 3; ++j)
		{
			shared_ptr<DecoObject> pDecoObject = make_shared<DecoObject>();
			pDecoObject->AddComponent(make_shared<Transform>());
			pDecoObject->GetTransform()->SetParent(GetTransform());

			pDecoObject->AddComponent(make_shared<Light>());
			pDecoObject->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
			pDecoObject->GetLight()->SetLightRange(150.f);
			pDecoObject->GetLight()->SetDiffuse(Vec3(0.5f, 0.5f, 0.f));

			pDecoObject->GetTransform()->SetLocalPosition(Vec3(-100.f + j * 75.f * 1.3f, i * 230.f - 170.f, 0.f));

			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDecoObject, eSceneType));
		}
	}
}
