#include "pch.h"
#include "Sequence.h"

BEHAVIOR_RESULT Sequence::Run()
{
	for (const shared_ptr<BehaviorNode> pChild : m_vChildren)
	{
		BEHAVIOR_RESULT eResult = pChild->Run();
		if (BEHAVIOR_RESULT::FAILURE == eResult)
			return BEHAVIOR_RESULT::FAILURE;

		else if (BEHAVIOR_RESULT::RUNNING == eResult)
			return BEHAVIOR_RESULT::RUNNING;

	}

	return BEHAVIOR_RESULT::SUCCESS;
}
