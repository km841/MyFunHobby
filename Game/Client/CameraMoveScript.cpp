#include "pch.h"
#include "CameraMoveScript.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"

CameraMoveScript::CameraMoveScript()
	:m_fSpeed(500.f)
{
}

CameraMoveScript::~CameraMoveScript()
{
}

void CameraMoveScript::LateUpdate()
{
	Vec3 vPos = GetTransform()->GetLocalPosition();

	if (IS_PRESS(KEY_TYPE::W))
	{
		vPos += GetTransform()->GetUp() * m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::S))
	{
		vPos -= GetTransform()->GetUp() * m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::A))
	{
		vPos -= GetTransform()->GetRight() * m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::D))
	{
		vPos += GetTransform()->GetRight() * m_fSpeed * DELTA_TIME;
	}

	GetTransform()->SetLocalPosition(vPos);
}
