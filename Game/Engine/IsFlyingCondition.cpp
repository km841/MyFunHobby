#include "pch.h"
#include "IsFlyingCondition.h"
#include "VeteranHero.h"

IsFlyingCondition::IsFlyingCondition(shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
{
}

IsFlyingCondition::~IsFlyingCondition()
{
}

BEHAVIOR_RESULT IsFlyingCondition::Run()
{
	weak_ptr<VeteranHero> pVeteranHero = static_pointer_cast<VeteranHero>(m_pGameObject.lock());
	return !pVeteranHero.lock()->IsGround() ? BEHAVIOR_RESULT::SUCCESS : BEHAVIOR_RESULT::FAILURE;
}
