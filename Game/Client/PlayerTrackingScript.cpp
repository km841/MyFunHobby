#include "pch.h"
#include "PlayerTrackingScript.h"
#include "Transform.h"
#include "Player.h"
#include "Physical.h"
#include "Clock.h"

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
	vPlayerPos.y += 200.f;
	const Vec3& vMyPos = GetTransform()->GetTransform()->GetLocalPosition();

	Vec3 vDiffNormal = vPlayerPos - vMyPos;
	if (1.f > vDiffNormal.Length())
		return;

	vDiffNormal.Normalize();
	vDiffNormal.y = 0.f;
	vDiffNormal.z = 0.f;
	GetTransform()->SetLocalPosition(vMyPos + vDiffNormal * 2000.f * DELTA_TIME);
}
