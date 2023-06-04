#include "pch.h"
#include "BGCameraScript.h"
#include "Transform.h"
#include "Player.h"
#include "Physical.h"
#include "Clock.h"
#include "RigidBody.h"
#include "Camera.h"

BGCameraScript::BGCameraScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

BGCameraScript::~BGCameraScript()
{
}

void BGCameraScript::LateUpdate()
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

	GetCamera()->SetCameraSpeed(vDiffNormal * 2000.f);
	GetTransform()->SetLocalPosition(vMyPos + vDiffNormal * 2000.f * OBJECT_DELTA_TIME);
}
