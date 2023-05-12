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
#include "GlobalEffect.h"
#include "Animator.h"
#include "Tile.h"

PlayerState::PlayerState(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
	, m_ePlayerState(PLAYER_STATE::END)
{
}

bool PlayerState::CheckGrounded()
{
	Vec3 vMyPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vMySize = m_pPlayer.lock()->GetPhysical()->GetGeometrySize();

	Vec3 vBtmLeft = Vec3(vMyPos.x - vMySize.x, vMyPos.y - vMySize.y, vMyPos.z);
	Vec3 vBtmCenter = Vec3(vMyPos.x, vMyPos.y - vMySize.y, vMyPos.z);
	Vec3 vBtmRight = Vec3(vMyPos.x + vMySize.x, vMyPos.y - vMySize.y, vMyPos.z);

	Vec3 vTopLeft = Vec3(vMyPos.x - vMySize.x, vMyPos.y + vMySize.y, vMyPos.z);
	Vec3 vTopCenter = Vec3(vMyPos.x, vMyPos.y + vMySize.y, vMyPos.z);
	Vec3 vTopRight = Vec3(vMyPos.x + vMySize.x, vMyPos.y + vMySize.y, vMyPos.z);

	const auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::TILE);

	bool bResult = {};
	Vec3 vBtmDir = -VEC3_UP_NORMAL;

	for (const auto& pGameObject : vGameObjects)
	{
		// 발판일 경우, 해당 타일의 겹침까지 확인
		switch (static_pointer_cast<Tile>(pGameObject)->GetTileType())
		{
		case TILE_TYPE::NONE:
			break;

		case TILE_TYPE::FOOTHOLD:
		{
			if (m_pPlayer.lock()->GetRigidBody()->GetVelocity(AXIS::Y) < 0.1f)
			{
				bool bCenterBtmResult = m_pPlayer.lock()->GetCollider()->Raycast(vBtmCenter, vBtmDir, pGameObject, 5.f);
				bool bLeftBtmResult = m_pPlayer.lock()->GetCollider()->Raycast(vBtmLeft, vBtmDir, pGameObject, 5.f);
				bool bRightBtmResult = m_pPlayer.lock()->GetCollider()->Raycast(vBtmRight, vBtmDir, pGameObject, 5.f);
				bool bLeftTopResult = m_pPlayer.lock()->GetCollider()->Raycast(vTopLeft, vBtmDir, pGameObject, vMySize.y - 5.f);
				bool bCenterTopResult = m_pPlayer.lock()->GetCollider()->Raycast(vTopCenter, vBtmDir, pGameObject, vMySize.y - 5.f);
				bool bRightTopResult = m_pPlayer.lock()->GetCollider()->Raycast(vTopRight, vBtmDir, pGameObject, vMySize.y - 5.f);

				if ( (bLeftBtmResult ||  bCenterBtmResult ||  bRightBtmResult) && 
				   ( !bLeftTopResult && !bCenterTopResult && !bRightTopResult) )
				{
					m_pPlayer.lock()->ReorganizeVerticalPosition();
					return true;
				}

			}
		}
			break;

		case TILE_TYPE::WALL:
		{
			bResult = m_pPlayer.lock()->GetCollider()->Raycast(vBtmLeft, vBtmDir, pGameObject, 5.f);
			if (bResult)
				return true;

			bResult = m_pPlayer.lock()->GetCollider()->Raycast(vBtmCenter, vBtmDir, pGameObject, 5.f);
			if (bResult)
				return true;

			bResult = m_pPlayer.lock()->GetCollider()->Raycast(vBtmRight, vBtmDir, pGameObject, 5.f);
			if (bResult)
				return true;
		}
			break;
		}

	}

	return false;
}

void PlayerState::AddChangeStateEvent(PLAYER_STATE ePlayerState)
{
	GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(m_pPlayer.lock(), ePlayerState));
}

void PlayerState::EnableAndInitJumpSmokeEffect()
{
	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3 vPlayerScale = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetLocalScale();

	vPlayerPos.y -= vPlayerScale.y / 2.f + 10.f;

	m_pPlayer.lock()->GetJumpSmokeEffect()->Enable();
	m_pPlayer.lock()->GetJumpSmokeEffect()->GetTransform()->SetLocalPosition(vPlayerPos);
	m_pPlayer.lock()->GetJumpSmokeEffect()->GetAnimator()->Play(L"DoubleJumpSmoke", false);
}