#include "pch.h"
#include "PlayerHitTask.h"
#include "Player.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transform.h"

PlayerHitTask::PlayerHitTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
{
}

BEHAVIOR_RESULT PlayerHitTask::Run()
{
	m_pPlayer.lock()->TakeDamage(1);
	GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.05f, Vec3(500.f, 0.f, 0.f));
	
	//if (m_pPlayer.lock()->DoesTileExistInDirection(m_pPlayer.lock()->GetDirection(), 2.f))
	//{
	//	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	//	Vec3 vMyPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	//	Vec3 vTargetVec = vPlayerPos - vMyPos;

	//	if (vTargetVec.x > 0.f)
	//	{
	//		vPlayerPos.x += 10.f;
	//	}
	//	else
	//	{
	//		vPlayerPos.x -= 10.f;
	//	}
	//	
	//	m_pPlayer.lock()->GetTransform()->SetPhysicalPosition(vPlayerPos);
	//}


	return BEHAVIOR_RESULT::SUCCESS;
}
