#include "pch.h"
#include "SkillState.h"
#include "SkulSkill.h"

SkillState::SkillState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
	m_ePlayerState = PLAYER_STATE::SKILL;
}

void SkillState::Update()
{
	// Skul이 스킬을 사용하면, 해당 스킬이 세팅되고, 그 스킬의 지속시간동안 유지된다.
	// ActiveSkill이 세팅되고, SkillState로 전이되어야 한다
	// if (ActiveSkul->ActiveSkill->IsFinished())
	//   ChangeState(Idle)
	// else
	//	 ActiveSkul->ActiveSkill->Update()
	// 
}

void SkillState::Enter()
{
	// 스컬이 사용한 스킬의 애니메이션이 출력
}

void SkillState::Exit()
{
	m_pPlayer.lock()->GetActiveSkul()->DisableSkillActiveFlag();
}
