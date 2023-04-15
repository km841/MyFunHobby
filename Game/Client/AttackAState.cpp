#include "pch.h"
#include "AttackAState.h"
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

AttackAState::AttackAState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::ATTACK_A;
}

void AttackAState::Update()
{
	weak_ptr<Animation> pActiveAnimation = m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock();
	// Path State 전이
	if (pActiveAnimation.lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
		return;
	}

	// Attack B State 전이
	float fProgress = pActiveAnimation.lock()->GetAnimationProgress();
	if (fProgress >= 0.75f && IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::ATTACK_B);
		return;
	}

	if (pActiveAnimation.lock()->CurrentIsHitFrame())
	{
		const AttackInfo& attackInfo = m_pPlayer.lock()->GetActiveSkul()->GetAttackInfo(ATTACK_ORDER::ATTACK_A);
		int a = 0;
		// Hit 처리
	}
	
	// Jump Rise State 전이
	if (!CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_RISE);
		return;
	}

	// Skill State 전이
	if (m_pPlayer.lock()->GetActiveSkul()->IsSkillActiveFlag())
	{
		SKILL_TYPE eSkillType = m_pPlayer.lock()->GetActiveSkul()->GetSkillActiveType();
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

void AttackAState::Enter()
{
	PlayAnimation();
}

void AttackAState::Exit()
{

}

void AttackAState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::ATTACK_A, false);
}
