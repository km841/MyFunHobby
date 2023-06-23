#include "pch.h"
#include "JumpRiseState.h"
#include "Player.h"
#include "Animator.h"
#include "Input.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"
#include "Sound.h"
#include "SoundSource.h"
#include "Resources.h"
#include "ComponentObject.h"

JumpRiseState::JumpRiseState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::JUMP_RISE;
}

void JumpRiseState::Update()
{
	// JumpFall State 전이
	const Vec3& vVelocity = m_pPlayer.lock()->GetRigidBody()->GetVelocity();
	if (vVelocity.y < 0.f)
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_FALL);
		return;
	}

	// JumpAttack State 전이
	if (IS_PRESS(KEY_TYPE::X))
	{
		AddChangeStateEvent(PLAYER_STATE::JUMP_ATTACK);
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

	// Swap State 전이
	if (m_pPlayer.lock()->IsSwapActiveFlag())
	{
		AddChangeStateEvent(PLAYER_STATE::SWAP);
		return;
	}

	// Idle State 전이
	if (CheckGrounded())
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}

	// Dash State 전이
	if (IS_PRESS(KEY_TYPE::Z))
	{
		AddChangeStateEvent(PLAYER_STATE::DASH);
		return;
	}

	if (IS_DOWN(KEY_TYPE::C) && m_pPlayer.lock()->GetJumpCount())
	{
		EnableAndInitJumpSmokeEffect();
	}
}

void JumpRiseState::Enter()
{
	PlayAnimation();
	m_pPlayer.lock()->GetRigidBody()->ApplyGravity();

	shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Jump_Normal", L"..\\Resources\\Sound\\Default_Jump.wav");
	SCENE_SOUND->SetClip(pSound);
	SCENE_SOUND->Play();
}

void JumpRiseState::Exit()
{
}

void JumpRiseState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::JUMP_RISE);
}
