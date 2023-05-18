#include "pch.h"
#include "IsPlayerNearCondition.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"

IsPlayerNearCondition::IsPlayerNearCondition(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
	, m_pPlayer(pPlayer)
{
}

IsPlayerNearCondition::~IsPlayerNearCondition()
{
}

BEHAVIOR_RESULT IsPlayerNearCondition::Run()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMonsterPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vTargetVec = vPlayerPos - vMonsterPos;
	
	const auto& status = m_pGameObject.lock()->GetStatus();
	if (vTargetVec.Length() < status->fRecogDist)
		return BEHAVIOR_RESULT::SUCCESS;

	else
		return BEHAVIOR_RESULT::FAILURE;
	
}
