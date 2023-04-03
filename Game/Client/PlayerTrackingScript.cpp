#include "pch.h"
#include "PlayerTrackingScript.h"
#include "Transform.h"
#include "Player.h"
#include "Physical.h"

PlayerTrackingScript::PlayerTrackingScript(shared_ptr<Player> pPlayer, float fDepth)
	: m_pPlayer(pPlayer)
	, m_fDepth(fDepth)
{
}

PlayerTrackingScript::~PlayerTrackingScript()
{
}

void PlayerTrackingScript::LateUpdate()
{
	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vMyPos = GetTransform()->GetTransform()->GetLocalPosition();
	GetTransform()->SetLocalPosition(Vec3(vPlayerPos.x, vMyPos.y, m_fDepth));
}
