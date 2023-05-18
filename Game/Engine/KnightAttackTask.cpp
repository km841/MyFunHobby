#include "pch.h"
#include "KnightAttackTask.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Player.h"
#include "Transform.h"
#include "Font.h"
#include "Engine.h"
#include "Scenes.h"
#include "Scene.h"
#include "Clock.h"

KnightAttackTask::KnightAttackTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
	, m_fSlidingRange(1100.f)
	, m_fSlidingSpeed(1000.f)
{
}

BEHAVIOR_RESULT KnightAttackTask::Run()
{
	weak_ptr<Animation> pAnimation = m_pGameObject.lock()->GetAnimator()->GetActiveAnimation();
	
	if (!pAnimation.lock())
		return BEHAVIOR_RESULT::FAILURE;

	uint8 iDirection = static_cast<uint8>(m_pGameObject.lock()->GetDirection());

	if (pAnimation.lock()->IsHitFrame())
	{
		const Status* status = m_pGameObject.lock()->GetStatus();
		m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(iDirection ? -m_fSlidingSpeed : m_fSlidingSpeed, 0.f, 0.f));

		Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
		Vec3 vMyPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
		Vec3 vTargetVec = vPlayerPos - vMyPos;
		Vec3 vTargetNormal = vTargetVec;
		vTargetNormal.Normalize();

		if (vTargetVec.Length() < 250.f)
		{
			Vec3 vNormal = iDirection ? -VEC3_RIGHT_NORMAL : VEC3_RIGHT_NORMAL;

			float fRadian = acos(vNormal.Dot(vTargetNormal));
			if (fRadian >= 0.f && fRadian <= XM_PI / 4.f)
			{
				m_pPlayer.lock()->TakeDamage(5);
				FONT->DrawDamage(DAMAGE_TYPE::FROM_MONSTER, 5.f, m_pPlayer.lock()->GetTransform()->GetPhysicalPosition());
				GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.05f, Vec3(500.f, 0.f, 0.f));
			}

		}

		pAnimation.lock()->CheckToHitFrame();
	}

	if (0.f < m_fSlidingRange)
	{
		m_fSlidingRange -= m_fSlidingSpeed * DELTA_TIME;
	}
	else
	{
		m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
	}

	if (pAnimation.lock()->IsFinished())
	{
		m_fSlidingRange = 1100.f;
		return BEHAVIOR_RESULT::SUCCESS;
	}

	return BEHAVIOR_RESULT::FAILURE;
}
