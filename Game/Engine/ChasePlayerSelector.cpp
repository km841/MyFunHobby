#include "pch.h"
#include "ChasePlayerSelector.h"

BEHAVIOR_RESULT ChasePlayerSelector::Run()
{
	if (IsPlayerInRange())
	{
		return BEHAVIOR_RESULT::SUCCESS;
	}

	return Selector::Run();
}

bool ChasePlayerSelector::IsPlayerInRange()
{
	// 플레이어와의 거리 계산
	return true;
}
