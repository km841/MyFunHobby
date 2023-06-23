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
#include "Player.h"
#include "ComponentObject.h"
#include "SoundSource.h"

ErodedHeavyInfantryDeadScript::ErodedHeavyInfantryDeadScript()
	: m_tStayTimer(1.7f)
	, m_bDeadBeginFlag(false)
{
}

ErodedHeavyInfantryDeadScript::~ErodedHeavyInfantryDeadScript()
{
}

void ErodedHeavyInfantryDeadScript::LateUpdate()
{
	weak_ptr<ErodedHeavyInfantry> pErodedInfantry = static_pointer_cast<ErodedHeavyInfantry>(GetGameObject());

	if (MONSTER_STATE::DEAD == pErodedInfantry.lock()->GetMonsterState())
	{
		if (!m_bDeadBeginFlag)
		{
			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Rage_Heavy", L"..\\Resources\\Sound\\Hardmode_Chapter3_Heavy_Rage_Voice.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
			m_bDeadBeginFlag = true;
		}
	}


	if (pErodedInfantry.lock()->GetDeadFlag())
	{
		if (!m_tStayTimer.IsRunning())
			m_tStayTimer.Start();

		m_tStayTimer.Update(OBJECT_DELTA_TIME);

		if (m_tStayTimer.IsFinished())
		{
			pErodedInfantry.lock()->ClearAttackCount();
			Vec3 vMyPos = pErodedInfantry.lock()->GetTransform()->GetPhysicalPosition();
			// BOOM!
			GET_SINGLE(CollisionManager)->SetForceInLayer(
				LAYER_TYPE::PARTICLE,
				vMyPos,
				Vec3(300.f, 300.f, 0.f),
				Vec3(0.f, 600.f, 0.f)
			);

			Vec3 vPlayerPos = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->GetPhysicalPosition();
			Vec3 vDiff = vPlayerPos - vMyPos;

			GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(
				vMyPos,
				Vec3(300.f, 300.f, 0.f),
				Vec3(vDiff.x < 0.f ? 300.f : -300.f, 1000.f, 0.f)
				, 8.f);

			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			pErodedInfantry.lock()->SetDeadFlag(false);
			CreateExplosionEffectAndAddedToScene();

			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Hardmode_Chapter3_Ultimate_Explosion", L"..\\Resources\\Sound\\Hardmode_Chapter3_Ultimate_Explosion.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
			m_bDeadBeginFlag = false;
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