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
	vPlayerPos.y += 100.f;
	//vPlayerPos.z = 0.f;
	const Vec3& vMyPos = GetTransform()->GetTransform()->GetLocalPosition();

	Vec3 vDiffNormal = vPlayerPos - vMyPos;
	if (1.f > vDiffNormal.Length())
	{
		GetTransform()->SetLocalPosition(vPlayerPos);
		return;
	}

	vDiffNormal.Normalize();
	vDiffNormal.y *= 2.f;
	vDiffNormal.z = 0.f;
	GetTransform()->SetLocalPosition(vMyPos + vDiffNormal * 1000.f * DELTA_TIME);
	//GetTransform()->SetLocalPosition(vPlayerPos);
}
