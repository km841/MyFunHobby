#include "pch.h"
#include "MadRushSkill.h"

MadRushSkill::MadRushSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
}

void MadRushSkill::Update()
{
	SkulSkill::Update();
	// 스킬 시전 중 공격 키가 눌리면 돌격하며 공격 애니메이션 + 슬래쉬 + 플래쉬

}

void MadRushSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void MadRushSkill::Enter()
{
}

void MadRushSkill::Exit()
{
}

void MadRushSkill::CreateSlashEffectAndAddedToScene()
{
}
