#include "pch.h"
#include "StayAnimLocalEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"
#include "Clock.h"

POOL_INIT(StayAnimLocalEffect);
StayAnimLocalEffect::StayAnimLocalEffect()
	: GameObject(LAYER_TYPE::LOCAL_EFFECT)
	, m_tStayTime(0.5f)
	, m_bStarted(false)
{
	
}

StayAnimLocalEffect::~StayAnimLocalEffect()
{
}

void StayAnimLocalEffect::Awake()
{
	GameObject::Awake();
}

void StayAnimLocalEffect::Start()
{
	GameObject::Start();
}

void StayAnimLocalEffect::Update()
{
	GameObject::Update();

	if (m_tStayTime.IsRunning())
	{
		m_tStayTime.Update(DELTA_TIME);
	}
	else
	{
		m_tStayTime.Start();
	}

	if (m_tStayTime.IsFinished())
	{
		if (GetAnimator())
		{
			if (!m_bStarted)
			{
				GetAnimator()->Play(L"Kirion_Slash_Dash", false);
				m_bStarted = true;
			}

			if (GetAnimator()->GetActiveAnimation()->IsFinished())
			{
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
				m_tStayTime.Reset();
				m_bStarted = false;
			}
		}
	}
}

void StayAnimLocalEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void StayAnimLocalEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}
