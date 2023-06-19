#include "pch.h"
#include "IsGroundCondition.h"
#include "VeteranHero.h"

IsGroundCondition::IsGroundCondition(shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
{
}

IsGroundCondition::~IsGroundCondition()
{
}

BEHAVIOR_RESULT IsGroundCondition::Run()
{
	weak_ptr<VeteranHero> pVeteranHero = static_pointer_cast<VeteranHero>(m_pGameObject.lock());
	return pVeteranHero.lock()->IsGround() ? BEHAVIOR_RESULT::SUCCESS : BEHAVIOR_RESULT::FAILURE;
}
