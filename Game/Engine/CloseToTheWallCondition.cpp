#include "pch.h"
#include "CloseToTheWallCondition.h"
#include "Transform.h"

CloseToTheWallCondition::CloseToTheWallCondition(shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
{
}

CloseToTheWallCondition::~CloseToTheWallCondition()
{
}

BEHAVIOR_RESULT CloseToTheWallCondition::Run()
{
	Vec3 vPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	DIRECTION eDirection = m_pGameObject.lock()->GetDirection();

	if (eDirection == DIRECTION::RIGHT && vPos.x < -200.f/*Left*/ || 
		eDirection == DIRECTION::LEFT  && vPos.x >  900.f/*Right*/)
		return BEHAVIOR_RESULT::SUCCESS;
	else
		return BEHAVIOR_RESULT::FAILURE;
}
