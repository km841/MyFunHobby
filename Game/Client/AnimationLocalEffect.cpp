#include "pch.h"
#include "AnimationLocalEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"

POOL_INIT(AnimationLocalEffect);
AnimationLocalEffect::AnimationLocalEffect()
	: GameObject(LAYER_TYPE::LOCAL_EFFECT)
{
}

AnimationLocalEffect::~AnimationLocalEffect()
{
}

void AnimationLocalEffect::Awake()
{
	GameObject::Awake();
}

void AnimationLocalEffect::Start()
{
	GameObject::Start();
}

void AnimationLocalEffect::Update()
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

void AnimationLocalEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void AnimationLocalEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void AnimationLocalEffect::ReturnToPool()
{
	AnimationLocalEffect::Release(static_pointer_cast<AnimationLocalEffect>(shared_from_this()));
}