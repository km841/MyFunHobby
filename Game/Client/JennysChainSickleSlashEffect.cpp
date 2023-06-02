#include "pch.h"
#include "JennysChainSickleSlashEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "Transform.h"

POOL_INIT(JennysChainSickleSlashEffect);
JennysChainSickleSlashEffect::JennysChainSickleSlashEffect()
{
}

JennysChainSickleSlashEffect::~JennysChainSickleSlashEffect()
{
}

void JennysChainSickleSlashEffect::Awake()
{
	LocalEffect::Awake();
}

void JennysChainSickleSlashEffect::Start()
{
	LocalEffect::Start();
}

void JennysChainSickleSlashEffect::Update()
{
	LocalEffect::Update();
	if (GetAnimator())
	{
		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			GET_SINGLE(CollisionManager)->SetForceInLayerAndFollowPlayer(
				LAYER_TYPE::PARTICLE,
				GetTransform()->GetWorldPosition(),
				GetTransform()->GetLocalScale(),
				Vec3(0.f, 100.f, 0.f));

			GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
				GetTransform()->GetWorldPosition(),
				GetTransform()->GetLocalScale(),
				Vec3(0.f, 0.f, 0.f),
				3.f,
				DAMAGE_TYPE::FROM_PLAYER_MELEE
			);


			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}

		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
		}
	}
}

void JennysChainSickleSlashEffect::LateUpdate()
{
	LocalEffect::LateUpdate();
}

void JennysChainSickleSlashEffect::FinalUpdate()
{
	LocalEffect::FinalUpdate();
}
