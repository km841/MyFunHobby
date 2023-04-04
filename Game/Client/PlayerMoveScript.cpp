#include "pch.h"
#include "PlayerMoveScript.h"
#include "Clock.h"
#include "Input.h"
#include "Transform.h"
#include "Controller.h"
#include "Physical.h"
#include "GameObject.h"
#include "Collider.h"
#include "Engine.h"
#include "RigidBody.h"
#include "UIManager.h"
#include "DialogueUI.h"
#include "Player.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "PlayerState.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(400.f)
	, m_fJumpSpeed(1000.f)
	, m_FilterShaders{}
{
}

PlayerMoveScript::~PlayerMoveScript()
{
}

void PlayerMoveScript::LateUpdate()
{
	Vec3 vVelocity = {};
	shared_ptr<Player> pPlayer = static_pointer_cast<Player>(GetGameObject());

	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		vVelocity = VEC3_RIGHT_NORMAL * -m_fSpeed;
		pPlayer->SetDirection(DIRECTION::LEFT);

		if (PLAYER_STATE::DASH != GetPlayerStateEnum())
			GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vVelocity = VEC3_RIGHT_NORMAL * m_fSpeed;
		pPlayer->SetDirection(DIRECTION::RIGHT);

		if (PLAYER_STATE::DASH != GetPlayerStateEnum())
			GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
	}

	if (IS_DOWN(KEY_TYPE::A))
	{
		weak_ptr<SkulSkill> pFirstSkill = pPlayer->GetActiveSkul()->GetSkill(SKILL_INDEX::FIRST).lock();
		if (pFirstSkill.lock() && 
			pFirstSkill.lock()->IsActive() && 
			pFirstSkill.lock()->IsCondition(pPlayer->GetActiveSkul()))
		{
			pPlayer->GetActiveSkul()->SetActiveSkill(SKILL_INDEX::FIRST);
			pPlayer->GetActiveSkul()->EnableSkillActiveFlag();
		}
	}

	if (IS_DOWN(KEY_TYPE::S))
	{
		weak_ptr<SkulSkill> pSecondSkill = pPlayer->GetActiveSkul()->GetSkill(SKILL_INDEX::SECOND).lock();
		if (pSecondSkill.lock() && 
			pSecondSkill.lock()->IsActive() && 
			pSecondSkill.lock()->IsCondition(pPlayer->GetActiveSkul()))
		{
			pPlayer->GetActiveSkul()->SetActiveSkill(SKILL_INDEX::SECOND);
			pPlayer->GetActiveSkul()->EnableSkillActiveFlag();
		}
	}

	if (IS_DOWN(KEY_TYPE::C))
	{
		if (pPlayer->GetJumpCount() && PLAYER_STATE::DASH != pPlayer->GetPlayerStateEnum())
		{
			vVelocity = VEC3_UP_NORMAL * m_fJumpSpeed;
			GetRigidBody()->SetVelocity(vVelocity);
			pPlayer->DecreaseJumpCount();

			if (PLAYER_STATE::JUMP_RISE == pPlayer->GetPlayerStateEnum() ||
				PLAYER_STATE::JUMP_FALL == pPlayer->GetPlayerStateEnum())
			{
				pPlayer->GetPlayerState().lock()->EnableAndInitJumpSmokeEffect();
			}
		}

		// Test Code
		//GetGameObject()->GetStatus()->TakeDamage(1);

		//GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->GetTransform()->SetLocalPosition(Vec3(800.f, 450.f, 80.f));
		//if (GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->IsEnable())
		//	GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->Disable();
		
		//else
		//	GET_SINGLE(UIManager)->Get(UI_TYPE::DIALOGUE)->Enable();
	}
}
