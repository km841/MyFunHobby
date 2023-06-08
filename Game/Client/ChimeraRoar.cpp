#include "pch.h"
#include "ChimeraRoar.h"
#include "Clock.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"

ChimeraRoar::ChimeraRoar()
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_tDuration(2.f)
{
}

ChimeraRoar::~ChimeraRoar()
{
}

void ChimeraRoar::Awake()
{
	GameObject::Awake();
}

void ChimeraRoar::Start()
{
	GameObject::Start();
}

void ChimeraRoar::Update()
{
	GameObject::Update();

	if (!m_tDuration.IsRunning())
		m_tDuration.Start();

	else
	{
		m_tDuration.Update(WORLD_DELTA_TIME);
		if (m_tDuration.IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
		}
	}
}

void ChimeraRoar::LateUpdate()
{
	GameObject::LateUpdate();
}

void ChimeraRoar::FinalUpdate()
{
	GameObject::FinalUpdate();
}
