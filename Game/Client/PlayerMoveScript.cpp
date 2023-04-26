#include "pch.h"
#include "PlayerMoveScript.h"
#include "Clock.h"
#include "Input.h"
#include "Transform.h"
#include "Physical.h"
#include "GameObject.h"
#include "Collider.h"
#include "Engine.h"
#include "RigidBody.h"
#include "InterfaceManager.h"
#include "DialogueUI.h"
#include "Player.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "PlayerState.h"


PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(400.f)
	, m_fJumpSpeed(1300.f)
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
		vVelocity = VEC3_RIGHT_NORMAL * -pPlayer->GetStatus()->fSpeed;
		
		if (PLAYER_STATE::DASH != GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != GetPlayerStateEnum())
		{
			pPlayer->SetDirection(DIRECTION::LEFT);
			if (pPlayer->DoesTileExistInDirection(DIRECTION::LEFT, 0.1f))
				GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
		}
	}

	else if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vVelocity = VEC3_RIGHT_NORMAL * pPlayer->GetStatus()->fSpeed;
	
		if (PLAYER_STATE::DASH != GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != GetPlayerStateEnum())
		{
			pPlayer->SetDirection(DIRECTION::RIGHT);
			if (pPlayer->DoesTileExistInDirection(DIRECTION::RIGHT, 0.1f))
				GetRigidBody()->SetVelocity(AXIS::X, vVelocity.x);
		}
	}

	if (IS_DOWN(KEY_TYPE::A))
	{
		weak_ptr<SkulSkill> pFirstSkill = pPlayer->GetActiveSkul()->GetSkill(SKILL_INDEX::FIRST).lock();
		if (pFirstSkill.lock() && 
			pFirstSkill.lock()->IsActive() && 
			pFirstSkill.lock()->IsCondition(pPlayer->GetActiveSkul()))
		{
			pPlayer->GetActiveSkul()->SetActiveSkill(SKILL_INDEX::FIRST);
			pPlayer->GetActiveSkul()->EnableSkillActiveFlag(pFirstSkill.lock()->GetSkillType());
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
			pPlayer->GetActiveSkul()->EnableSkillActiveFlag(pSecondSkill.lock()->GetSkillType());
		}
	}

	if (IS_DOWN(KEY_TYPE::C))
	{
		if (pPlayer->GetJumpCount() && 
			PLAYER_STATE::DASH != pPlayer->GetPlayerStateEnum() && 
			PLAYER_STATE::CHARGING != pPlayer->GetPlayerStateEnum())
		{
			vVelocity = VEC3_UP_NORMAL * m_fJumpSpeed;
			GetRigidBody()->SetVelocity(vVelocity);
			pPlayer->DecreaseJumpCount();
		}

		// Test Code
		//pPlayer->TakeDamage(1);

		//GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)->GetTransform()->SetLocalPosition(Vec3(800.f, 450.f, 80.f));
		//if (GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)->IsEnable())
		//	GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)->Disable();
		//
		//else
		//	GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)->Enable();
	}

	if (IS_NONE(KEY_TYPE::LEFT) && IS_NONE(KEY_TYPE::RIGHT))
	{
		if (PLAYER_STATE::DASH != pPlayer->GetPlayerStateEnum() &&
			PLAYER_STATE::SWAP != pPlayer->GetPlayerStateEnum())
			GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	}

	pPlayer->ReorganizePosition();
	pPlayer->ReorganizePosition();
	//pPlayer->CheckAndAdjustPlayerPositionOnCollision();

	if (IS_DOWN(KEY_TYPE::SPACE))
	{
		if (pPlayer->IsSwapPossible())
			pPlayer->EnableSwapActiveFlag();
	}
}
