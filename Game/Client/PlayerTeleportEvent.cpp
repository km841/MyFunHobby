#include "pch.h"
#include "PlayerTeleportEvent.h"
#include "Scenes.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"
#include "ComponentObject.h"

PlayerTeleportEvent::PlayerTeleportEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vPlayerPos)
	: DungeonEvent(DUNGEON_EVENT_KIND::PLAYER_TELEPORT, pConditionBlock)
	, m_vDescPos(vPlayerPos)
{
}

PlayerTeleportEvent::~PlayerTeleportEvent()
{
}

void PlayerTeleportEvent::Update()
{
	DungeonEvent::Update();
}

void PlayerTeleportEvent::ExecuteEvent()
{
	Vec3 vPlayerPos = m_vDescPos;
	vPlayerPos.z -= 1.f;
	GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->SetPhysicalPosition(vPlayerPos);


	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetTransform()->SetLocalPosition(Vec3(m_vDescPos.x, m_vDescPos.y, 1.f));
	GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetRigidBody()->SetVelocity(Vec3::Zero);
}
