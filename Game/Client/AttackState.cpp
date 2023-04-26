#include "pch.h"
#include "AttackState.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Input.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Transform.h"
#include "Physical.h"
#include "Engine.h"
#include "Scenes.h"
#include "Animation.h"
#include "SkulAttack.h"
#include "MeshRenderer.h"
#include "Material.h"

AttackState::AttackState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void AttackState::Update()
{
	weak_ptr<Skul> pActiveSkul = m_pPlayer.lock()->GetActiveSkul();
	weak_ptr<SkulAttack> pAttackMethod = pActiveSkul.lock()->GetAttackMethod().lock();
	weak_ptr<Animation> pActiveAnimation = pActiveSkul.lock()->GetActiveAnimation().lock();

	// Path State 전이 & Attack Method 진행
	if (pAttackMethod.lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
		return;
	}
	else
	{
		pAttackMethod.lock()->Update();
	}

	// Jump Rise State 전이
	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	// Skill State 전이
	if (pActiveSkul.lock()->IsSkillActiveFlag())
	{
		SKILL_TYPE eSkillType = pActiveSkul.lock()->GetSkillActiveType();
		switch (eSkillType)
		{
		case SKILL_TYPE::INSTANT:
			AddChangeStateEvent(PLAYER_STATE::SKILL);
			break;
		case SKILL_TYPE::CHARGING:
			AddChangeStateEvent(PLAYER_STATE::CHARGING);
			break;
		}
		return;
	}

	// Dash State 전이
	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}
}

void AttackState::Enter()
{
	m_pPlayer.lock()->GetActiveSkul()->GetAttackMethod().lock()->Enter();
	m_pPlayer.lock()->GetActiveSkul()->GetMeshRenderer()->GetMaterial()->SetInt(3, 1);
}

void AttackState::Exit()
{
	m_pPlayer.lock()->GetActiveSkul()->GetAttackMethod().lock()->Exit();
	m_pPlayer.lock()->GetActiveSkul()->GetMeshRenderer()->GetMaterial()->SetInt(3, 0);
}