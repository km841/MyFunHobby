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
		// �ش�Ǵ� ������ �ִ� ���͵鿡�� Hit �÷��׸� �����ش�
		// ���͵��� �ൿƮ�������� �� ó�� �� Hit Flag�� �˻��� ��
		// �� Hit Flag�� �ö� ������ Hit �ִϸ��̼��� n�ʰ� ����Ѵ�.
		// Ÿ�� ����Ʈ��? �÷��̾ �����ϰ� �ִٰ� �ѷ��ֳ�?
		// 20�� ���� ������ ������ �ִٰ� Ÿ�� �� �ѷ��ش�
		// ���Ͱ� �ϳ��� ������ �ִ´�?
		// Hit���� �����ʰ� ���ÿ� ����Ʈ ����

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
