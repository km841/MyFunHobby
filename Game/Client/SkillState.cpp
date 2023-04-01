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
	// Skul�� ��ų�� ����ϸ�, �ش� ��ų�� ���õǰ�, �� ��ų�� ���ӽð����� �����ȴ�.
	// ActiveSkill�� ���õǰ�, SkillState�� ���̵Ǿ�� �Ѵ�
	// if (ActiveSkul->ActiveSkill->IsFinished())
	//   ChangeState(Idle)
	// else
	//	 ActiveSkul->ActiveSkill->Update()
	// 
}

void SkillState::Enter()
{
	// ������ ����� ��ų�� �ִϸ��̼��� ���
}

void SkillState::Exit()
{
	m_pPlayer.lock()->GetActiveSkul()->DisableSkillActiveFlag();
}
