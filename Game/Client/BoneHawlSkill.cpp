#include "pch.h"
#include "BoneHawlSkill.h"

BoneHawlSkill::BoneHawlSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
	CreateConditionFunction();
}

void BoneHawlSkill::Update()
{
	SkulSkill::Update();
}

void BoneHawlSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void BoneHawlSkill::Enter()
{
}

void BoneHawlSkill::Exit()
{
}
