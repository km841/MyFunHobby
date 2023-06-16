#include "pch.h"
#include "VeteranHeroLandingScript.h"
#include "VeteranHero.h"
#include "RigidBody.h"
#include "Physical.h"

VeteranHeroLandingScript::VeteranHeroLandingScript()
	: m_bLandingReadyCompleteFlag(false)
	, m_bLandingCompleteFlag(false)
	, m_bLandingThrowingFlag(false)
{
}

VeteranHeroLandingScript::~VeteranHeroLandingScript()
{
}

void VeteranHeroLandingScript::LateUpdate()
{
	weak_ptr<VeteranHero> pVeteranHero = static_pointer_cast<VeteranHero>(GetGameObject());

	if (MONSTER_STATE::LANDING_READY == pVeteranHero.lock()->GetMonsterState())
	{
		if (!m_bLandingReadyCompleteFlag)
		{
			PxVec3 vNormal = PxVec3(-1.f, 1.f, 0.f);
			vNormal.normalize();
			GetRigidBody()->SetLinearVelocityForDynamic(vNormal * 700.f);
			GetPhysical()->GetActor<PxRigidDynamic>()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
			m_bLandingReadyCompleteFlag = true;
		}
	}

	if (MONSTER_STATE::LANDING_THROWING == pVeteranHero.lock()->GetMonsterState())
	{
		if (!m_bLandingThrowingFlag)
		{
			m_bLandingThrowingFlag = true;
		}
	}

}
