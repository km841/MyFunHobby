#include "pch.h"
#include "ErodedHeavyInfantryAttackScript.h"
#include "Monster.h"
#include "AnimationLocalEffect.h"
#include "ObjectFactory.h"
#include "Animator.h"
#include "Animation.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "CollisionManager.h"

ErodedHeavyInfantryAttackScript::ErodedHeavyInfantryAttackScript()
	: m_bAttackFlag(false)
{
}

ErodedHeavyInfantryAttackScript::~ErodedHeavyInfantryAttackScript()
{
}

void ErodedHeavyInfantryAttackScript::LateUpdate()
{
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(GetGameObject());

	if (MONSTER_STATE::ATTACK_READY == pMonster.lock()->GetMonsterState())
	{
		if (!m_bAttackFlag)
		{
			m_bAttackFlag = true;
			CreateAttackSignAndAddedToScene();
		}
	}
	else
	{
		m_bAttackFlag = false;
	}

	if (MONSTER_STATE::ATTACK == pMonster.lock()->GetMonsterState())
	{
		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			GET_SINGLE(CollisionManager)->SetForceInLayer(
				LAYER_TYPE::PARTICLE,
				vMyPos,
				Vec3(1500.f, 300.f, 0.f),
				Vec3(0.f, 1500.f, 0.f));

			GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(
				vMyPos,
				Vec3(1500.f, 300.f, 0.f),
				Vec3(0.f, 1500.f, 0.f)
				, 8.f);

			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}
	}
}

void ErodedHeavyInfantryAttackScript::CreateAttackSignAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	pAnimationLocalEffect->GetTransform()->SetParent(GetTransform());
	pAnimationLocalEffect->GetTransform()->SetLocalPosition(Vec3(0.f, -30.f, -1.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Attack_Sign", L"..\\Resources\\Animation\\MonsterCommon\\monster_common_attack_sign.anim");
	pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Attack_Sign", pAnimation);
	pAnimationLocalEffect->GetAnimator()->Play(L"Attack_Sign", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}
