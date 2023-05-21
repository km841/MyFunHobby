#include "pch.h"
#include "IsPlayerNearCondition.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"

IsPlayerNearCondition::IsPlayerNearCondition(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject, float fDistance)
	: BehaviorCondition(pGameObject)
	, m_pPlayer(pPlayer)
	, m_fDistance(fDistance)
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
	if (m_fDistance < 0.1f)
		m_fDistance = status->fRecogDist;

	if (vTargetVec.Length() < m_fDistance)
		return BEHAVIOR_RESULT::SUCCESS;

	else
		return BEHAVIOR_RESULT::FAILURE;
	
}
