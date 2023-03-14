#include "pch.h"
#include "PlayerMoveScript.h"
#include "Timer.h"
#include "Input.h"
#include "Transform.h"
#include "Controller.h"

PlayerMoveScript::PlayerMoveScript()
	: m_fSpeed(5.f)
{

}

PlayerMoveScript::~PlayerMoveScript()
{

}

void PlayerMoveScript::LateUpdate()
{
	Vec3 vPos = {};

	if (IS_PRESS(KEY_TYPE::UP))
	{
		vPos = GetTransform()->GetUp() * m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::DOWN))
	{
		vPos = GetTransform()->GetUp() * -m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::LEFT))
	{
		vPos = GetTransform()->GetRight() * -m_fSpeed * DELTA_TIME;
	}

	if (IS_PRESS(KEY_TYPE::RIGHT))
	{
		vPos = GetTransform()->GetRight() * m_fSpeed * DELTA_TIME;
	}

	PlayerFilterShaders filter = PlayerFilterShaders();
	
	PxFilterData filterData = {};
	filterData.word0 = 1 << 0;
	filterData.word1 = 1 << 1;

	GetController()->Move(Conv::Vec3ToPxVec3(vPos), &filter, filterData);
}
