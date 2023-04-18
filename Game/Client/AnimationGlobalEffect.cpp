#include "pch.h"
#include "AnimationGlobalEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"

POOL_INIT(AnimationGlobalEffect);
AnimationGlobalEffect::AnimationGlobalEffect()
	: GlobalEffect(0.f)
{
}

AnimationGlobalEffect::~AnimationGlobalEffect()
{
}

void AnimationGlobalEffect::Awake()
{
	GlobalEffect::Awake();
}

void AnimationGlobalEffect::Start()
{
	GlobalEffect::Start();
}

void AnimationGlobalEffect::Update()
{
	GlobalEffect::Update();
	if (GetAnimator())
	{
		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
		}
	}
}

void AnimationGlobalEffect::LateUpdate()
{
	GlobalEffect::LateUpdate();
}

void AnimationGlobalEffect::FinalUpdate()
{
	GlobalEffect::FinalUpdate();
}

void AnimationGlobalEffect::ReturnToPool()
{
	AnimationGlobalEffect::Release(static_pointer_cast<AnimationGlobalEffect>(shared_from_this()));
}
