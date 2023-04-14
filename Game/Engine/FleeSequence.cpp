#include "pch.h"
#include "FleeSequence.h"

BEHAVIOR_RESULT FleeSequence::Run()
{
	if (IsPlayerOutOfRange())
	{
		return BEHAVIOR_RESULT::RUNNING;
	}

	return Sequence::Run();
}

void FleeSequence::StopSkill()
{
	// 몬스터 스킬 사용 정지
}

bool FleeSequence::IsPlayerOutOfRange()
{
	return true;
}
