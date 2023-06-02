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
#include "Player.h"
#include "Engine.h"

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

			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(100.f, 1000.f, 0.f));
			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}
	}

	if (MONSTER_STATE::RAGE_ATTACK == pMonster.lock()->GetMonsterState())
	{
		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();

			Vec3 vVolume = Vec3(300.f, 600.f, 1.f);
			weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
			Vec3 vPlayerPos = pPlayer.lock()->GetTransform()->GetPhysicalPosition();

			Vec3 vDiff = vPlayerPos - vMyPos;
			uint8 iDirection = static_cast<uint8>(pMonster.lock()->GetDirection());

			Vec3 vLeftTop = Vec3(vMyPos.x + (iDirection ? -vVolume.x: 0.f), vMyPos.y + vVolume.y, 0.f);
			Vec3 vRightBtm = Vec3(vMyPos.x + (iDirection ? 0.f : vVolume.x), vMyPos.y - 100.f, 0.f);

			if (vPlayerPos.x > vLeftTop.x && vPlayerPos.x < vRightBtm.x &&
				vPlayerPos.y > vRightBtm.y && vPlayerPos.y < vLeftTop.y)
			{
				pPlayer.lock()->TakeDamage(4);
				FONT->DrawDamage(DAMAGE_TYPE::FROM_MONSTER, 4.f, vPlayerPos);
			}

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
