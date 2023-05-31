#include "pch.h"
#include "ObjectAttackAtHitFrameScript.h"
#include "Animator.h"
#include "Animation.h"
#include "GameObject.h"
#include "Player.h"
#include "Engine.h"
#include "Transform.h"
#include "CollisionManager.h"

ObjectAttackAtHitFrameScript::ObjectAttackAtHitFrameScript(shared_ptr<GameObject> pGameObject, DAMAGE_TYPE eDamageType, float fDamage)
	: m_pGameObject(pGameObject)
	, m_eDamageType(eDamageType)
	, m_fDamage(fDamage)
{
}

ObjectAttackAtHitFrameScript::~ObjectAttackAtHitFrameScript()
{
}

void ObjectAttackAtHitFrameScript::LateUpdate()
{
	if (!GetAnimator())
		return;

	if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
	{
		Vec3 vObjectPos = {};

		if (m_pGameObject.lock()->GetPhysical())
			vObjectPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
		else
			vObjectPos = m_pGameObject.lock()->GetTransform()->GetLocalPosition();

		Vec3 vVolume = m_pGameObject.lock()->GetTransform()->GetLocalScale();
		if (LAYER_TYPE::PLAYER == m_pGameObject.lock()->GetLayerType())
		{
			GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(vObjectPos, vVolume, Vec3(0.f, 0.f, 0.f), m_fDamage, m_eDamageType);
		}
		else
		{
			if (DAMAGE_TYPE::FROM_MONSTER == m_eDamageType)
				GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vObjectPos, vVolume, Vec3(0.f, 0.f, 0.f), m_fDamage);

			else
				GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(vObjectPos, vVolume, Vec3(0.f, 0.f, 0.f), m_fDamage, m_eDamageType);

		}
		GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
	}
}
