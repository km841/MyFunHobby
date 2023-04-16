#include "pch.h"
#include "SkulAttack.h"
#include "Animation.h"
#include "Skul.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transform.h"
#include "Player.h"
#include "Monster.h"

SkulAttack::SkulAttack(shared_ptr<Skul> pSkul)
	: m_eActiveAttackOrder(ATTACK_ORDER::ATTACK_A)
	, m_pSkul(pSkul)
	, m_iMaxCount(0)
{
}

bool SkulAttack::IsFinished()
{
	uint8 iEnum = m_pSkul.lock()->GetEnumIndex();
	return m_arrAttackInfo[iEnum][static_cast<uint8>(m_eActiveAttackOrder)].pAnimation->IsFinished();
}

void SkulAttack::HitMonstersInAttackRange()
{
	shared_ptr<Scene> pActiveScene =GET_SINGLE(Scenes)->GetActiveScene();
	auto& vGameObjects = pActiveScene->GetGameObjects(LAYER_TYPE::MONSTER);

	uint8 iEnum = m_pSkul.lock()->GetEnumIndex();
	uint8 iOrder = static_cast<uint8>(m_eActiveAttackOrder);

	float fRadius = m_arrAttackInfo[iEnum][iOrder].fRadius;
	float fStartAngle = m_arrAttackInfo[iEnum][iOrder].fStartAngle;
	float fEndAngle = m_arrAttackInfo[iEnum][iOrder].fEndAngle;

	Vec3 vMyPos = m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPhysicalPosition();
	vMyPos.z = 0.f;

	DIRECTION eDirection = m_pSkul.lock()->GetDirection();
	Vec3 vRightNormal = VEC3_RIGHT_NORMAL;
	if (DIRECTION::LEFT == eDirection)
		vRightNormal = -vRightNormal;


	for (auto& pGameObject : vGameObjects)
	{
		Vec3 vPos = pGameObject->GetTransform()->GetPhysicalPosition();
		vPos.z = 0.f;

		Vec3 vTargetVec = vPos - vMyPos;
		float fDistance = vTargetVec.Length();

		Vec3 vTargetNormal = vTargetVec;
		vTargetNormal.Normalize();

		if (fDistance <= fRadius)
		{
			float fRadian = acos(vRightNormal.Dot(vTargetNormal));
			float fDegree = (fRadian * 180.f) / XM_PI;
			if (fDegree > fStartAngle && fDegree < fEndAngle)
			{
				static_pointer_cast<Monster>(pGameObject)->FlagAsAttacked();
			}
		}
	}

}

void SkulAttack::AddAttackInfo(ATTACK_ORDER eAttackOrder, const AttackInfo& attackInfo)
{
	uint8 iAttackOrder = static_cast<uint8>(eAttackOrder);
	assert(iAttackOrder < ATTACK_ORDER_COUNT);
	uint8 iEnum = attackInfo.iEnum;
	m_arrAttackInfo[iEnum][iAttackOrder] = attackInfo;
	m_iMaxCount++;
}