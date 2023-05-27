#include "pch.h"
#include "SkulAttack.h"
#include "Animation.h"
#include "Skul.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transform.h"
#include "Player.h"
#include "Monster.h"
#include "Physical.h"
#include "ParticleSystem.h"
#include "GlobalEffect.h"
#include "Engine.h"
#include "CollisionManager.h"

SkulAttack::SkulAttack(shared_ptr<Skul> pSkul)
	: m_eActiveAttackOrder(ATTACK_ORDER::ATTACK_A)
	, m_pSkul(pSkul)
	, m_iMaxCount(0)
	, m_fDamage(1)
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

	GET_SINGLE(CollisionManager)->SetForceInLayer(
		LAYER_TYPE::PARTICLE,
		Vec3(vMyPos.x + (DIRECTION::LEFT == eDirection ? -100.f : 100.f), vMyPos.y, vMyPos.z),
		Vec3(fRadius * 2.f, fRadius * 2.f, 0.f),
		Vec3(DIRECTION::LEFT == eDirection ? -100.f : 100.f, 100.f, 0.f));

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
				shared_ptr<Monster> pMonster = static_pointer_cast<Monster>(pGameObject);

				if (MONSTER_STATE::DEAD <= pMonster->GetMonsterState())
					continue;

				if (MONSTER_TYPE::NORMAL == pMonster->GetMonsterType())
					pMonster->SetMonsterState(MONSTER_STATE::WEAK_HIT);

				CreateHitEffectAndAddedScene(vPos);
				Damage damage = CalculateDamage();
				
				pGameObject->GetStatus()->TakeDamage(static_cast<int32>(damage.second));
				FONT->DrawDamage(damage.first, damage.second, vPos);

				// Monster Dead Event Occurs
				if (!pGameObject->GetStatus()->IsAlive())
				{
					pMonster->SetMonsterState(MONSTER_STATE::DEAD);
					pMonster->SetParticleDir(Vec3(vTargetVec.x < 0.f ? -400.f : 400.f, 400.f, 0.f));
					static_pointer_cast<Monster>(pGameObject)->ActivateDeadEvent(Vec3(vTargetVec.x < 0.f ? -400.f : 400.f, 400.f, 0.f));
				}

				// Generate Particles
				pMonster->GetParticleGenerator().lock()->GetParticleSystem()->SetParticleAliveCount(30);
				pMonster->GetParticleGenerator().lock()->GetParticleSystem()->SetParticleDirection(Vec3(vTargetVec.x < 0.f ? -500.f : 500.f, 500.f, 0.f));
			}

			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.05f, Vec3(500.f, 0.f, 0.f));
		}
	}
}

Damage SkulAttack::CalculateDamage()
{
	float fDamage = m_pSkul.lock()->GetPlayer().lock()->GetStatus()->iAttack + m_fDamage;
	float fCritical = m_pSkul.lock()->GetPlayer().lock()->GetStatus()->fCriticalPercent;
	bool bIsCritical = RANDOM(1, 100) <= fCritical;
	DAMAGE_TYPE eDamageType = bIsCritical ? DAMAGE_TYPE::FROM_PLAYER_CRITICAL : DAMAGE_TYPE::FROM_PLAYER_MELEE;

	return std::make_pair(eDamageType, bIsCritical ? fDamage * 1.5f : fDamage);
}


void SkulAttack::AddAttackInfo(ATTACK_ORDER eAttackOrder, const AttackInfo& attackInfo)
{
	uint8 iAttackOrder = static_cast<uint8>(eAttackOrder);
	assert(iAttackOrder < ATTACK_ORDER_COUNT);
	uint8 iEnum = attackInfo.iEnum;
	m_arrAttackInfo[iEnum][iAttackOrder] = attackInfo;
	m_iMaxCount++;
}