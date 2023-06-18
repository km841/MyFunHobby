#include "pch.h"
#include "SetVelocityGoToPlayerPosTask.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"

SetVelocityGoToPlayerPosTask::SetVelocityGoToPlayerPosTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject, float fVelocity)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
	, m_fVelocity(fVelocity)
{
}

SetVelocityGoToPlayerPosTask::~SetVelocityGoToPlayerPosTask()
{
}

BEHAVIOR_RESULT SetVelocityGoToPlayerPosTask::Run()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMonsterPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vTargetVec = vPlayerPos - vMonsterPos;
	
	m_pGameObject.lock()->GetRigidBody()->SetVelocity(Vec3(vTargetVec.x < 0.f ? -m_fVelocity : m_fVelocity, 0.f, 0.f));

	return BEHAVIOR_RESULT::SUCCESS;
}
