#include "pch.h"
#include "BackgroundMoveScript.h"
#include "Transform.h"
#include "Clock.h"
#include "GameObject.h"

BackgroundMoveScript::BackgroundMoveScript(float fSpeed)
	:m_fSpeed(fSpeed)
{
}

BackgroundMoveScript::~BackgroundMoveScript()
{
}

void BackgroundMoveScript::LateUpdate()
{
	const Vec3& vMyPos = GetGameObject()->GetTransform()->GetLocalPosition();
	Vec3 vNextPos = Vec3(vMyPos.x + m_fSpeed * DELTA_TIME, vMyPos.y, vMyPos.z);
	if (vNextPos.x < -1500.f)
		vNextPos.x = 4500.f;
	GetGameObject()->GetTransform()->SetLocalPosition(vNextPos);
}
