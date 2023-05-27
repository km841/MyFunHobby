#include "pch.h"
#include "ErodedEntDeadScript.h"
#include "ErodedEnt.h"
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
#include "Player.h"

ErodedEntDeadScript::ErodedEntDeadScript()
	: m_tStayTimer(1.5f)
{
}

ErodedEntDeadScript::~ErodedEntDeadScript()
{
}

void ErodedEntDeadScript::LateUpdate()
{
	weak_ptr<ErodedEnt> pErodedEnt = static_pointer_cast<ErodedEnt>(GetGameObject());

	if (pErodedEnt.lock()->GetDeadFlag())
	{
		if (!m_tStayTimer.IsRunning())
			m_tStayTimer.Start();

		m_tStayTimer.Update(DELTA_TIME);

		if (m_tStayTimer.IsFinished())
		{
			Vec3 vMyPos = pErodedEnt.lock()->GetTransform()->GetPhysicalPosition();

			// BOOM!
			GET_SINGLE(CollisionManager)->SetForceInLayer(
				LAYER_TYPE::PARTICLE,
				pErodedEnt.lock()->GetTransform()->GetPhysicalPosition(),
				Vec3(300.f, 300.f, 0.f),
				Vec3(0.f, 600.f, 0.f)
			);

			Vec3 vPlayerPos = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->GetPhysicalPosition();
			Vec3 vDiff = vPlayerPos - vMyPos;

			GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(
				vMyPos,
				Vec3(200.f, 200.f, 0.f),
				Vec3(vDiff.x < 0.f ? 300.f : -300.f, 1000.f, 0.f)
				, 8.f);

			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			pErodedEnt.lock()->SetDeadFlag(false);
			CreateExplosionEffectAndAddedToScene();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(pErodedEnt.lock()->GetExclamationEffect().lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(GetGameObject(), eSceneType));
		}
	}
}

void ErodedEntDeadScript::CreateExplosionEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(GetTransform()->GetPhysicalPosition());
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 50.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedMonsterExplosion", L"..\\Resources\\Animation\\MonsterCommon\\eroded_monster_explosion.anim");
	pAnimationLocalEffect->GetAnimator()->AddAnimation(L"ErodedMonsterExplosion", pAnimation);
	pAnimationLocalEffect->GetAnimator()->Play(L"ErodedMonsterExplosion", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}
