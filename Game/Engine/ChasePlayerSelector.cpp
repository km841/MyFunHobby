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
	// �÷��̾���� �Ÿ� ���
	return true;
}
