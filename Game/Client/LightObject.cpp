#include "pch.h"
#include "LightObject.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Light.h"


LightObject::LightObject()
	: GameObject(LAYER_TYPE::LIGHT_OBJECT)
{
}

LightObject::~LightObject()
{
}

void LightObject::Awake()
{
	GameObject::Awake();
}

void LightObject::Start()
{
	GameObject::Start();
}

void LightObject::Update()
{
	GameObject::Update();
}

void LightObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void LightObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void LightObject::CreateLightAndAddedToScene()
{
	shared_ptr<GameObject> pDecoObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
	pDecoObject->AddComponent(make_shared<Transform>());
	pDecoObject->GetTransform()->SetParent(GetTransform());

	pDecoObject->AddComponent(make_shared<Light>());
	pDecoObject->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
	pDecoObject->GetLight()->SetLightRange(300.f);
	pDecoObject->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));

	pDecoObject->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -5.f));

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDecoObject, eSceneType));
}
