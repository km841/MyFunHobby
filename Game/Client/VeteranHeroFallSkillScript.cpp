#include "pch.h"
#include "VeteranHeroFallSkillScript.h"
#include "VeteranHero.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Transform.h"
#include "Clock.h"
#include "Scenes.h"
#include "Scene.h"
#include "Player.h"
#include "Animator.h"
#include "AnimationLocalEffect.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "MagicSword.h"
#include "ComponentObject.h"
#include "SoundSource.h"

VeteranHeroFallSkillScript::VeteranHeroFallSkillScript()
	: m_bSkillReadyFlag(false)
	, m_bSkillFlag(false)
	, m_tDelayTime(2.f)
	, m_tFallStayTime(3.f)
	, m_bWarningSignFlag(false)
{
}

VeteranHeroFallSkillScript::~VeteranHeroFallSkillScript()
{
}

void VeteranHeroFallSkillScript::LateUpdate()
{
	weak_ptr<VeteranHero> pVeteranHero = static_pointer_cast<VeteranHero>(GetGameObject());
	MONSTER_STATE eMonsterState = pVeteranHero.lock()->GetMonsterState();
	if (MONSTER_STATE::SKILL1_READY == pVeteranHero.lock()->GetMonsterState())
	{
		if (!m_bSkillReadyFlag)
		{
			GetRigidBody()->SetVelocity(Vec3(0.f, 2000.f, 0.f));
			m_bSkillReadyFlag = true;
			CreateJumpSmokeAndAddedToScene();
		}

		Vec3 vPos = GetTransform()->GetPhysicalPosition();
		if (vPos.y > 300.f)
		{
			GetRigidBody()->RemoveGravity();
			pVeteranHero.lock()->SetMonsterState(MONSTER_STATE::SKILL1);
			pVeteranHero.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
			m_tDelayTime.Start();
		}
	}

	if (MONSTER_STATE::SKILL1 == pVeteranHero.lock()->GetMonsterState())
	{
		m_tDelayTime.Update(WORLD_DELTA_TIME);
		if (!m_bWarningSignFlag)
		{
			CreateWarningSignAndAddedToScene();
			m_bWarningSignFlag = true;
		}

		if (!m_bSkillFlag && m_tDelayTime.IsFinished())
		{
			GetAnimator()->Play(L"VeteranHero_FallDown", false);
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(0.f, 300.f, 0.f));
			GetRigidBody()->RemoveGravity();
			m_vFallDownPos.z += 1.f;
			m_vFallDownPos.y = -450.f;
			GetTransform()->SetPhysicalPosition(m_vFallDownPos);
			m_bSkillFlag = true;
			m_tFallStayTime.Start();

			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Hero_Landing", L"..\\Resources\\Sound\\Hero_Landing.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
			

			CreateMagicSwordsAndAddedToScene();
			// Spawn Swords
		}

		if (m_bSkillFlag && m_tFallStayTime.IsFinished())
		{
			pVeteranHero.lock()->SetMonsterState(MONSTER_STATE::IDLE);
			m_tFallStayTime.Reset();
			m_tDelayTime.Reset();
			m_bSkillFlag = false;
			m_bSkillReadyFlag = false;
			m_bWarningSignFlag = false;
		}
		else
		{
			m_tFallStayTime.Update(WORLD_DELTA_TIME);
		}
	}
	
}

void VeteranHeroFallSkillScript::CreateJumpSmokeAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pEffect =
		GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	pEffect->AddComponent(make_shared<Animator>());

	// Venom Ball Despawn
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_JumpSmoke", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_jump_smoke.anim");
		pEffect->GetAnimator()->AddAnimation(L"VeteranHero_JumpSmoke", pAnimation);
	}
	pEffect->GetAnimator()->Play(L"VeteranHero_JumpSmoke", false);

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos += Vec3(0.f, 30.f, 0.f);
	pEffect->GetTransform()->SetLocalPosition(vPos);

	pEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pEffect, eSceneType));
}

void VeteranHeroFallSkillScript::CreateWarningSignAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	
	Vec3 vPlayerPos = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->GetPhysicalPosition();
	vPlayerPos.z -= 1.f;
	vPlayerPos.y = -400.f;

	m_vFallDownPos = vPlayerPos;
	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPlayerPos);

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Attack_Sign", L"..\\Resources\\Animation\\MonsterCommon\\default_attack_sign.anim");
	pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Attack_Sign", pAnimation);
	pAnimationLocalEffect->GetAnimator()->Play(L"Attack_Sign", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}

void VeteranHeroFallSkillScript::CreateMagicSwordsAndAddedToScene()
{
	for (int32 i = 0; i < 3; ++i)
	{
		for (int32 j = 0; j < 2; ++j)
		{
			shared_ptr<MagicSword> pSword = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MagicSword>(L"Forward", L"", i * 0.3f);

			float fOffset = 100.f * (i + 1);
			Vec3 vPos = GetTransform()->GetPhysicalPosition();
			vPos.z -= 1.f;
			vPos.x += j ? -fOffset : fOffset;
			vPos.y = -450.f;
			pSword->GetTransform()->SetLocalPosition(vPos);

			pSword->AddComponent(make_shared<Animator>());
			shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MagicSword", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_magic_sword.anim");
			pSword->GetAnimator()->AddAnimation(L"MagicSword", pAnimation);

			pAnimation->SetHitFrame(1);

			pSword->Awake();
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSword, eSceneType));
		}

	}

}
