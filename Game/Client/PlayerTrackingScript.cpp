#include "pch.h"
#include "PlayerTrackingScript.h"
#include "Transform.h"
#include "Player.h"
#include "Physical.h"
#include "Clock.h"
#include "RigidBody.h"
#include "Camera.h"
#include "Engine.h"

PlayerTrackingScript::PlayerTrackingScript(shared_ptr<Player> pPlayer, float fDepth)
	: m_pPlayer(pPlayer)
	, m_fDepth(fDepth)
	, m_fTrackingSpeed(2000.f)
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

	float fTrackingSpeed = m_fTrackingSpeed;
	const Vec4& vLimitRect = GetCamera()->GetLimitRect();
	if (Vec4::Zero != vLimitRect)
	{
		float fWidth = static_cast<float>(g_pEngine->GetWidth());
		float fHeight = static_cast<float>(g_pEngine->GetHeight());
		Vec3 vNextPos = vMyPos + vDiffNormal * fTrackingSpeed * WORLD_DELTA_TIME;
		
		float fCheckLeftX = vNextPos.x - fWidth / 2.f;
		float fCheckRightX = vNextPos.x + fWidth / 2.f;
		float fCheckTopY = vNextPos.y + fHeight / 2.f;
		float fCheckBtmY = vNextPos.y - fHeight / 2.f;

		if (fCheckLeftX < vLimitRect.x)
			vNextPos.x = vLimitRect.x + fWidth / 2.f;
		if (fCheckRightX > vLimitRect.z)
			vNextPos.x = vLimitRect.z - fWidth / 2.f;
		if (fCheckTopY > vLimitRect.y)
			vNextPos.y = vLimitRect.y - fHeight / 2.f;
		if (fCheckBtmY < vLimitRect.w)
			vNextPos.y = vLimitRect.w + fHeight / 2.f;

		GetTransform()->SetLocalPosition(vNextPos);

	}
	else
	{
		GetTransform()->SetLocalPosition(vMyPos + vDiffNormal * fTrackingSpeed * WORLD_DELTA_TIME);
	}


}
