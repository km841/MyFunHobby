#include "pch.h"
#include "IsPlayerInAttackRangeCondition.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "Scene.h"
#include "Scenes.h"

IsPlayerInAttackRangeCondition::IsPlayerInAttackRangeCondition(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
	, m_pPlayer(pPlayer)
{
}

IsPlayerInAttackRangeCondition::~IsPlayerInAttackRangeCondition()
{
}

BEHAVIOR_RESULT IsPlayerInAttackRangeCondition::Run()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMyPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();

	Vec3 vTargetVec = vPlayerPos - vMyPos;

	if (m_pGameObject.lock()->GetAnimator()->GetActiveAnimation()->IsHitFrame())
	{
		if (vTargetVec.Length() < 400.f)
		{
			if (vTargetVec.x > 0.f)
			{
				Vec3 vRightNormal = VEC3_RIGHT_NORMAL;
				Vec3 vTargetNormal = vTargetVec;
				vTargetNormal.Normalize();
				float fRadian = acos(vRightNormal.Dot(vTargetNormal));

				if (fRadian > 0.f && fRadian < XM_PI / 4.f)
				{
					// Hit!
					m_pPlayer.lock()->TakeDamage(1);
					GET_SINGLE(Scenes)->GetActiveScene()->CameraShakeAxis(0.05f, Vec3(500.f, 0.f, 0.f));
				}
			
			}
			else
			{
				Vec3 vRightNormal = -VEC3_RIGHT_NORMAL;
				Vec3 vTargetNormal = vTargetVec;
				vTargetNormal.Normalize();
				float fRadian = acos(vRightNormal.Dot(vTargetNormal));

				if (fRadian > 0.f && fRadian < XM_PI / 4.f)
				{
					// Hit!
					m_pPlayer.lock()->TakeDamage(1);
					GET_SINGLE(Scenes)->GetActiveScene()->CameraShakeAxis(0.05f, Vec3(500.f, 0.f, 0.f));
				}
			}
		}

		m_pGameObject.lock()->GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
