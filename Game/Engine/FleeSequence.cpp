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
	// ���� ��ų ��� ����
}

bool FleeSequence::IsPlayerOutOfRange()
{
	return true;
}
