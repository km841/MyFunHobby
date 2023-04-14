#include "pch.h"
#include "UseSkillTask.h"

UseSkillTask::UseSkillTask(std::function<BEHAVIOR_RESULT()> fnTask)
	: BehaviorTask(fnTask)
{
}

BEHAVIOR_RESULT UseSkillTask::Run()
{
	UseSkill();
	return BEHAVIOR_RESULT::SUCCESS;
}

void UseSkillTask::UseSkill()
{
	// 스킬 사용
}
