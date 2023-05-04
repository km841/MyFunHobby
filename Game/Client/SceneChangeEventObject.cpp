#include "pch.h"
#include "SceneChangeEventObject.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"
#include "Player.h"
#include "Transform.h"
#include "Engine.h"
#include "Scene.h"
#include "Scenes.h"
#include "ComponentObject.h"
#include "RigidBody.h"

SceneChangeEventObject::SceneChangeEventObject(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

SceneChangeEventObject::~SceneChangeEventObject()
{
}

void SceneChangeEventObject::Awake()
{
	EventObject::Awake();
}

void SceneChangeEventObject::Start()
{
	EventObject::Start();
}

void SceneChangeEventObject::Update()
{
	EventObject::Update();
}

void SceneChangeEventObject::LateUpdate()
{
	EventObject::LateUpdate();
}

void SceneChangeEventObject::FinalUpdate()
{
	EventObject::FinalUpdate();
}

void SceneChangeEventObject::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<SceneChangeEvent>(SCENE_TYPE::DUNGEON));

		// Temp Code
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
		m_pPlayer.lock()->GetTransform()->SetPhysicalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 200.f, 100.f));
		GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 500.f, 1.f));
		GET_SINGLE(Scenes)->GetActiveScene()->GetBGCamera().lock()->GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight / 2.f + 500.f, 1.f));
	}
}
