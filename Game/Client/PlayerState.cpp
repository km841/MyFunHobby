#include "pch.h"
#include "PlayerState.h"
#include "Player.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"

PlayerState::PlayerState(shared_ptr<Player> pPlayer)
	:m_pPlayer(pPlayer)
{
}

bool PlayerState::CheckGrounded()
{
	Vec3 vMyPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vMySize = m_pPlayer.lock()->GetPhysical()->GetGeometrySize();

	Vec3 vFootPos = Vec3(vMyPos.x, vMyPos.y - vMySize.y, vMyPos.z);
	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);

	RaycastResult bRaycastResult = {};
	Vec3 vBtmDir = -VEC3_UP_NORMAL;

	for (const auto& pGameObject : vGameObjects)
	{
		bRaycastResult = m_pPlayer.lock()->GetCollider()->Raycast(vFootPos, vBtmDir, pGameObject, 0.1f);

		if (bRaycastResult.first)
			return true;
	}

	return false;
}

void PlayerState::AddChangeStateEvent(PLAYER_STATE ePlayerState)
{
	GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), ePlayerState));
}

