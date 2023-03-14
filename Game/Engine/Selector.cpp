#include "pch.h"
#include "Selector.h"

BEHAVIOR_RESULT Selector::Run()
{
	for (const shared_ptr<BehaviorNode>& pChild : m_vChildren)
	{
		BEHAVIOR_RESULT eResult = pChild->Run();
		
		if (BEHAVIOR_RESULT::SUCCESS == eResult)
			return BEHAVIOR_RESULT::SUCCESS;

		else if (BEHAVIOR_RESULT::RUNNING == eResult)
			return BEHAVIOR_RESULT::RUNNING;

	}

	return BEHAVIOR_RESULT::FAILURE;
}
