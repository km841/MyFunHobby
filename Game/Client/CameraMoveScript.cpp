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

	//if (IS_PRESS(KEY_TYPE::Q))
	//{
	//	Vec3 vRotation = GetTransform()->GetLocalRotation();
	//	vRotation.x += DELTA_TIME * 0.5f;
	//	GetTransform()->SetLocalRotation(vRotation);
	//}

	//if (IS_PRESS(KEY_TYPE::E))
	//{
	//	Vec3 vRotation = GetTransform()->GetLocalRotation();
	//	vRotation.x -= DELTA_TIME * 0.5f;
	//	GetTransform()->SetLocalRotation(vRotation);
	//}

	//if (IS_PRESS(KEY_TYPE::Z))
	//{
	//	Vec3 vRotation = GetTransform()->GetLocalRotation();
	//	vRotation.y += DELTA_TIME * 0.5f;
	//	GetTransform()->SetLocalRotation(vRotation);
	//}

	//if (IS_PRESS(KEY_TYPE::C))
	//{
	//	Vec3 vRotation = GetTransform()->GetLocalRotation();
	//	vRotation.y -= DELTA_TIME * 0.5f;
	//	GetTransform()->SetLocalRotation(vRotation);
	//}

	GetTransform()->SetLocalPosition(vPos);
}
