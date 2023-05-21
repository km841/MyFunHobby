#include "pch.h"
#include "SetDirectionTowardPlayerTask.h"
#include "Player.h"
#include "Transform.h"

SetDirectionTowardPlayerTask::SetDirectionTowardPlayerTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
{
}

BEHAVIOR_RESULT SetDirectionTowardPlayerTask::Run()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMonsterPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vTargetVec = vPlayerPos - vMonsterPos;

	m_pGameObject.lock()->SetDirection(vTargetVec.x < 0.f ? DIRECTION::LEFT : DIRECTION::RIGHT);
	return BEHAVIOR_RESULT::SUCCESS;
}
