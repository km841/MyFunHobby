#include "pch.h"
#include "AbyssFieldDamageTickScript.h"
#include "Clock.h"
#include "CollisionManager.h"
#include "Transform.h"

AbyssFieldDamageTickScript::AbyssFieldDamageTickScript()
	: m_tDamageTick(0.2f)
{
}

AbyssFieldDamageTickScript::~AbyssFieldDamageTickScript()
{
}

void AbyssFieldDamageTickScript::LateUpdate()
{
	if (!m_tDamageTick.IsRunning())
		m_tDamageTick.Start();

	m_tDamageTick.Update(OBJECT_DELTA_TIME);

	const Vec3& vSize = GetTransform()->GetLocalScale();
	Vec3 vMyPos = GetTransform()->GetLocalPosition();

	if (m_tDamageTick.IsFinished())
	{
		GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
			vMyPos,
			vSize * 2.f,
			Vec3(0.f, 0.f, 0.f),
			static_cast<float>(RANDOM(1, 5)), DAMAGE_TYPE::FROM_PLAYER_MAGIC, L"..\\Resources\\Sound\\Hit_Blunt_Large.wav");

		m_tDamageTick.Reset();
	}
}
