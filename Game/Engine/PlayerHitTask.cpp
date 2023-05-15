#include "pch.h"
#include "PlayerHitTask.h"
#include "Player.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transform.h"
#include "Font.h"
#include "Engine.h"

PlayerHitTask::PlayerHitTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
{
}

BEHAVIOR_RESULT PlayerHitTask::Run()
{
	m_pPlayer.lock()->TakeDamage(5);
	FONT->DrawDamage(DAMAGE_TYPE::FROM_MONSTER, 5.f, m_pPlayer.lock()->GetTransform()->GetPhysicalPosition());
	GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.05f, Vec3(500.f, 0.f, 0.f));

	return BEHAVIOR_RESULT::SUCCESS;
}
