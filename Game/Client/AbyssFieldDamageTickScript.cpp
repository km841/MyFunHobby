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

	m_tDamageTick.Update(DELTA_TIME);

	const Vec3& vSize = GetTransform()->GetLocalScale();
	Vec3 vMyPos = GetTransform()->GetLocalPosition();

	if (m_tDamageTick.IsFinished())
	{
		GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
			vMyPos,
			vSize * 2.f,
			Vec3(0.f, 0.f, 0.f),
			1.f, DAMAGE_TYPE::FROM_PLAYER_MAGIC);

		m_tDamageTick.Reset();
	}
}
