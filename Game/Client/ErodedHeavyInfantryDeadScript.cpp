#include "pch.h"
#include "ErodedHeavyInfantryDeadScript.h"
#include "ErodedHeavyInfantry.h"
#include "Clock.h"
#include "AnimationLocalEffect.h"
#include "EventManager.h"
#include "ObjectReturnToPoolEvent.h"
#include "ObjectRemoveToSceneEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Animator.h"
#include "LocalEffect.h"
#include "CollisionManager.h"

ErodedHeavyInfantryDeadScript::ErodedHeavyInfantryDeadScript()
	: m_tStayTimer(1.7f)
{
}

ErodedHeavyInfantryDeadScript::~ErodedHeavyInfantryDeadScript()
{
}

void ErodedHeavyInfantryDeadScript::LateUpdate()
{
	weak_ptr<ErodedHeavyInfantry> pErodedInfantry = static_pointer_cast<ErodedHeavyInfantry>(GetGameObject());

	if (pErodedInfantry.lock()->GetDeadFlag())
	{
		if (!m_tStayTimer.IsRunning())
			m_tStayTimer.Start();

		m_tStayTimer.Update(DELTA_TIME);

		if (m_tStayTimer.IsFinished())
		{
			// BOOM!
			GET_SINGLE(CollisionManager)->SetForceInLayer(
				LAYER_TYPE::PARTICLE,
				pErodedInfantry.lock()->GetTransform()->GetPhysicalPosition(),
				Vec3(300.f, 300.f, 0.f),
				Vec3(0.f, 600.f, 0.f)
			);

			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			pErodedInfantry.lock()->SetDeadFlag(false);
			CreateExplosionEffectAndAddedToScene();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(pErodedInfantry.lock()->GetExclamationEffect().lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(GetGameObject(), eSceneType));
		}
	}
}

void ErodedHeavyInfantryDeadScript::CreateExplosionEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(GetTransform()->GetPhysicalPosition());
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedMonsterExplosion", L"..\\Resources\\Animation\\MonsterCommon\\eroded_huge_monster_explosion.anim");
	pAnimationLocalEffect->GetAnimator()->AddAnimation(L"ErodedMonsterExplosion", pAnimation);
	pAnimationLocalEffect->GetAnimator()->Play(L"ErodedMonsterExplosion", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}