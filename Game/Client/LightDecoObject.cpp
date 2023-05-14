#include "pch.h"
#include "LightDecoObject.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Light.h"


LightDecoObject::LightDecoObject()
	: DecoObject(DECO_OBJECT_TYPE::LIGHT)
{
}

LightDecoObject::~LightDecoObject()
{
}

void LightDecoObject::Awake()
{
	DecoObject::Awake();
	CreateLightAndAddedToScene();
}

void LightDecoObject::Start()
{
	DecoObject::Start();
}

void LightDecoObject::Update()
{
	DecoObject::Update();
}

void LightDecoObject::LateUpdate()
{
	DecoObject::LateUpdate();
}

void LightDecoObject::FinalUpdate()
{
	DecoObject::FinalUpdate();
}

void LightDecoObject::CreateLightAndAddedToScene()
{
	shared_ptr<GameObject> pDecoObject = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
	pDecoObject->AddComponent(make_shared<Transform>());
	pDecoObject->GetTransform()->SetParent(GetTransform());

	pDecoObject->AddComponent(make_shared<Light>());
	pDecoObject->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
	pDecoObject->GetLight()->SetLightRange(250.f);
	pDecoObject->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));

	pDecoObject->GetTransform()->SetLocalPosition(Vec3(0.f, -10.f, -5.f));

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDecoObject, eSceneType));
}
