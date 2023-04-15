#include "pch.h"
#include "SkulAttack.h"
#include "Animation.h"
#include "Skul.h"

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

void SkulAttack::AddAttackInfo(ATTACK_ORDER eAttackOrder, const AttackInfo& attackInfo)
{
	uint8 iAttackOrder = static_cast<uint8>(eAttackOrder);
	assert(iAttackOrder < ATTACK_ORDER_COUNT);
	uint8 iEnum = attackInfo.iEnum;
	m_arrAttackInfo[iEnum][iAttackOrder] = attackInfo;
	m_iMaxCount++;
}