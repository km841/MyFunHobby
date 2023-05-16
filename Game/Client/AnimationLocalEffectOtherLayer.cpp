#include "pch.h"
#include "AnimationLocalEffectOtherLayer.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"

POOL_INIT(AnimationLocalEffectOtherLayer);
AnimationLocalEffectOtherLayer::AnimationLocalEffectOtherLayer()
	: GameObject(LAYER_TYPE::BEFORE_LOCAL_EFFECT)
{
}

AnimationLocalEffectOtherLayer::~AnimationLocalEffectOtherLayer()
{
}

void AnimationLocalEffectOtherLayer::Awake()
{
	GameObject::Awake();
}

void AnimationLocalEffectOtherLayer::Start()
{
	GameObject::Start();
}

void AnimationLocalEffectOtherLayer::Update()
{
	GameObject::Update();
	if (GetAnimator())
	{
		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
		}
	}
}

void AnimationLocalEffectOtherLayer::LateUpdate()
{
	GameObject::LateUpdate();
}

void AnimationLocalEffectOtherLayer::FinalUpdate()
{
	GameObject::FinalUpdate();
}
