#include "pch.h"
#include "MadRushSkill.h"

MadRushSkill::MadRushSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
}

void MadRushSkill::Update()
{
	SkulSkill::Update();
	// ��ų ���� �� ���� Ű�� ������ �����ϸ� ���� �ִϸ��̼� + ������ + �÷���

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
