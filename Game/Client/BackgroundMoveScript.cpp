#include "pch.h"
#include "BackgroundMoveScript.h"
#include "Player.h"
#include "RigidBody.h"

BackgroundMoveScript::BackgroundMoveScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

BackgroundMoveScript::~BackgroundMoveScript()
{
}

void BackgroundMoveScript::LateUpdate()
{


	if (m_pPlayer.lock()->GetRigidBody()->IsAccelerating())
	{
		if (PLAYER_STATE::ATTACK_A != m_pPlayer.lock()->GetPlayerStateEnum() &&
			PLAYER_STATE::ATTACK_B != m_pPlayer.lock()->GetPlayerStateEnum() &&
			PLAYER_STATE::SKILL != m_pPlayer.lock()->GetPlayerStateEnum())
		{
			float fVelocity = m_pPlayer.lock()->GetRigidBody()->GetVelocity(AXIS::X);
			GetRigidBody()->SetVelocity(AXIS::X, fVelocity / 10.f);
		}

		else
		{
			GetRigidBody()->SetVelocity(AXIS::X, 0.f);
		}
	}
	else
	{
		GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	}
	
}
