#include "pch.h"
#include "PlayerTrackingScript.h"
#include "Transform.h"
#include "Player.h"
#include "Physical.h"
#include "Clock.h"
#include "RigidBody.h"
#include "Camera.h"

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

	// Temp Code
	if (vPlayerPos.y < -3000.f)
	{
		if (vPlayerPos.y < -3200.f)
		{
			m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
			m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
		}
		return;
	}

	vDiffNormal.Normalize();
	vDiffNormal.y *= 2.f;
	vDiffNormal.z = 0.f;
	GetCamera()->SetCameraSpeed(vDiffNormal * 2000.f);
	GetTransform()->SetLocalPosition(vMyPos + vDiffNormal * 2000.f * DELTA_TIME);
}
