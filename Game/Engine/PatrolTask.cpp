#include "pch.h"
#include "PatrolTask.h"
#include "Transform.h"
#include "RigidBody.h"
#include "GameObject.h"
#include "Clock.h"
#include "Collider.h"
#include "Scenes.h"
#include "Scene.h"
#include "Tile.h"

PatrolTask::PatrolTask(shared_ptr<GameObject> pGameObject, float fStartDistance, float fEndDistance)
	: BehaviorTask(pGameObject)
	, m_fStartDist(fStartDistance)
	, m_fEndDist(fEndDistance)
	, m_fRandDist(0.f)
	, m_bSettingDist(false)
	, m_bIsTileInDirection(false)
{
}

BEHAVIOR_RESULT PatrolTask::Run()
{
	uint8 iDirection = static_cast<uint8>(m_pGameObject.lock()->GetDirection());

	if (!m_bSettingDist)
	{
		m_fRandDist = static_cast<float>(RANDOM(static_cast<int32>(m_fStartDist), static_cast<int32>(m_fEndDist)));
		m_bSettingDist = true;

		if (m_bIsTileInDirection)
		{
			m_pGameObject.lock()->SetDirection(static_cast<DIRECTION>((iDirection + 1) % 2));

			m_vPrevPosition = Vec3::Zero;
			m_bIsTileInDirection = false;
		}
		else
		{
			m_pGameObject.lock()->SetDirection(static_cast<DIRECTION>((iDirection + RANDOM(0, 1)) % 2));
		}
	}

	else
	{
		const Status* status = m_pGameObject.lock()->GetStatus();
		PxVec3 vVelocity = PxVec3(status->fSpeed, 0.f, 0.f);

		m_fRandDist -= vVelocity.x * DELTA_TIME;
		vVelocity.x = iDirection ? -vVelocity.x : vVelocity.x;

		m_pGameObject.lock()->GetTransform()->GetRigidBody()->SetLinearVelocityForDynamic(vVelocity);
		if (m_fRandDist < 0.f)
		{
			m_bSettingDist = false;
			return BEHAVIOR_RESULT::SUCCESS;
		}

		Vec3 vCurPosition = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
		if ((vCurPosition - m_vPrevPosition).Length() < 0.1f)
		{
			m_bSettingDist = false;
			m_bIsTileInDirection = true;
			return BEHAVIOR_RESULT::SUCCESS;
		}

		m_vPrevPosition = vCurPosition;
	}
	return BEHAVIOR_RESULT::FAILURE;
	
}
