#include "pch.h"
#include "LittleBoneAttack.h"
#include "LittleBone.h"
#include "Animation.h"
#include "Input.h"

LittleBoneAttack::LittleBoneAttack(shared_ptr<Skul> pSkul)
	: SkulAttack(pSkul)
{
}

LittleBoneAttack::~LittleBoneAttack()
{
}

void LittleBoneAttack::Update()
{
	uint8 iEnum = m_pSkul.lock()->GetEnumIndex();
	uint8 iOrder = static_cast<uint8>(m_eActiveAttackOrder);
	float fProgress = m_arrAttackInfo[iEnum][iOrder].pAnimation->GetAnimationProgress();
	if (IS_DOWN(KEY_TYPE::X) && fProgress > 0.75f && iOrder < m_iMaxCount - 1)
	{
		m_eActiveAttackOrder = static_cast<ATTACK_ORDER>(iOrder + 1);
		m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
	}

	if (m_arrAttackInfo[iEnum][iOrder].pAnimation->CurrentIsHitFrame())
	{
		// 해당되는 범위에 있는 몬스터들에게 Hit 플래그를 세워준다
		// 몬스터들의 행동트리에서는 맨 처음 이 Hit Flag를 검사한 후
		// 이 Hit Flag가 올라가 있으면 Hit 애니메이션을 n초간 재생한다.
		// 타격 이펙트는? 플레이어가 소유하고 있다가 뿌려주나?
		// 20개 정도 씬에서 가지고 있다가 타격 시 뿌려준다
		// 몬스터가 하나씩 가지고 있는다?
		// Hit으로 설정됨과 동시에 이펙트 실행

		HitMonstersInAttackRange();
	}
}

void LittleBoneAttack::Enter()
{
	m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
}

void LittleBoneAttack::Exit()
{
	m_eActiveAttackOrder = ATTACK_ORDER::ATTACK_A;
}
