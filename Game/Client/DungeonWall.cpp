#include "pch.h"
#include "DungeonWall.h"
#include "DecoObject.h"
#include "ObjectFactory.h"
#include "Scene.h"
#include "Scenes.h"
#include "Light.h"
#include "Clock.h"

DungeonWall::DungeonWall(STAGE_KIND eStageKind)
	: GameObject(LAYER_TYPE::DUNGEON_WALL)
	, m_eStageKind(eStageKind)
	, m_bClearFlag(false)
{
}

DungeonWall::~DungeonWall()
{
}

void DungeonWall::Awake()
{
	GameObject::Awake();
	CreateLightAndAddedToScene();
}

void DungeonWall::Start()
{
	GameObject::Start();
}

void DungeonWall::Update()
{
	GameObject::Update();

	if (m_bClearFlag)
	{
		Vec3 vDiffuse = m_pLight.lock()->GetLight()->GetDiffuse();
		if (vDiffuse.x > 1.f)
			m_bClearFlag = false;

		m_pLight.lock()->GetLight()->AddDiffuse(Vec3(.5f, .5f, .5f) * DELTA_TIME);
	}

}

void DungeonWall::LateUpdate()
{
	GameObject::LateUpdate();
}

void DungeonWall::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DungeonWall::CreateLightAndAddedToScene()
{
	shared_ptr<DecoObject> pLight = make_shared<DecoObject>();
	pLight->AddComponent(make_shared<Transform>());
	pLight->GetTransform()->SetParent(GetTransform());
	pLight->GetTransform()->SetLocalPosition(Vec3(0.f, 100.f, 0.f));
	pLight->AddComponent(make_shared<Light>());
	pLight->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
	pLight->GetLight()->SetLightRange(1000.f);
	pLight->GetLight()->SetDiffuse(Vec3(0.f, 0.f, 0.f));
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLight, eSceneType));

	m_pLight = pLight;
}
