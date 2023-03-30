#include "pch.h"
#include "PlayerTrackingScript.h"
#include "Transform.h"
#include "Player.h"
#include "Physical.h"

PlayerTrackingScript::PlayerTrackingScript(shared_ptr<Player> pPlayer)
{
	m_pPlayer = pPlayer;
}

PlayerTrackingScript::~PlayerTrackingScript()
{
}

void PlayerTrackingScript::LateUpdate()
{
	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vMyPos = GetTransform()->GetTransform()->GetLocalPosition();
	GetTransform()->SetLocalPosition(Vec3(vPlayerPos.x, vMyPos.y, 1.f));
}