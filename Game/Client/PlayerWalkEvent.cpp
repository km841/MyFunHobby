#include "pch.h"
#include "PlayerWalkEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Player.h"
#include "RigidBody.h"

PlayerWalkEvent::PlayerWalkEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vVelocity, float fDuration)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAYER_WALK, pConditionBlock)
	, m_vVelocity(vVelocity)
	, m_fDuration(fDuration)
{
}

PlayerWalkEvent::~PlayerWalkEvent()
{
}

void PlayerWalkEvent::Update()
{
	DungeonEvent::Update();
}

void PlayerWalkEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetRigidBody()->ReserveSpeedForSeconds(m_vVelocity, m_fDuration);
}
