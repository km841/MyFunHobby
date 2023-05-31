#include "pch.h"
#include "ErodedEntSkillScript.h"
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
#include "ObjectAttackAtHitFrameScript.h"

ErodedEntSkillScript::ErodedEntSkillScript()
	: m_bSkillFlag(false)
	, m_bSkillSignFlag(false)
{
}

ErodedEntSkillScript::~ErodedEntSkillScript()
{
}

void ErodedEntSkillScript::LateUpdate()
{
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(GetGameObject());

	if (MONSTER_STATE::SKILL1_READY == pMonster.lock()->GetMonsterState())
	{
		if (Vec3::Zero == m_vPlayerPos)
		{
			m_vPlayerPos = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->GetPhysicalPosition();
			m_vPlayerPos.z -= 1.f;
		}

		if (!m_bSkillSignFlag)
		{
			m_bSkillSignFlag = true;
			CreateSkillSignAndAddedToScene();
		}
	}

	if (MONSTER_STATE::SKILL1 == pMonster.lock()->GetMonsterState())
	{
		if (!m_bSkillFlag)
		{
			m_bSkillFlag = true;
			CreateSkillEffectAndAddedToScene();
		}
	}

	if (MONSTER_STATE::SKILL1_END == pMonster.lock()->GetMonsterState())
	{
		m_bSkillFlag = false;
		m_bSkillSignFlag = false;
		m_vPlayerPos = Vec3::Zero;
	}
}

void ErodedEntSkillScript::CreateSkillSignAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	Vec3 vSignPos = m_vPlayerPos;
	vSignPos.z -= 1.f;

	pLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 45.f));
	pLocalEffect->GetTransform()->SetLocalPosition(vSignPos);
	pLocalEffect->AddComponent(make_shared<Animator>());

	// Skill Sign Animation
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Skill_Sign", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_skill_sign.anim");
		pLocalEffect->GetAnimator()->AddAnimation(L"Skill_Sign", pAnimation);
	}

	pLocalEffect->GetAnimator()->Play(L"Skill_Sign", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));
}

void ErodedEntSkillScript::CreateSkillEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	
	pLocalEffect->AddComponent(make_shared<ObjectAttackAtHitFrameScript>(pLocalEffect, DAMAGE_TYPE::FROM_MONSTER, 3.f));
	pLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, -25.f));
	pLocalEffect->GetTransform()->SetLocalPosition(m_vPlayerPos);
	pLocalEffect->AddComponent(make_shared<Animator>());

	// Skill Effect Animation
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Skill_Effect", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_thorn_effect.anim");
		pLocalEffect->GetAnimator()->AddAnimation(L"Skill_Effect", pAnimation);

		pAnimation->SetHitFrame(2);
	}

	pLocalEffect->GetAnimator()->Play(L"Skill_Effect", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));
}
