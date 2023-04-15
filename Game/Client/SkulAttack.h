#pragma once
class Skul;
class SkulAttack
{
public:
	friend class Skul;
	SkulAttack(shared_ptr<Skul> pSkul);
	virtual ~SkulAttack() = default;

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	void  AddAttackInfo(ATTACK_ORDER eAttackOrder, const AttackInfo& attackInfo);
	bool  IsFinished();
	
	// �ִϸ��̼��� ������ �� ����
	// ��ų�� �ð��� �������� �Ѵٸ� ������ �ִϸ��̼��� ������ ���� �������� �Ѵ�.

protected:
	uint8 m_iMaxCount;
	weak_ptr<Skul> m_pSkul;
	ATTACK_ORDER m_eActiveAttackOrder;
	std::array<std::array<AttackInfo, ATTACK_ORDER_COUNT>, MAX_ENUMS> m_arrAttackInfo;
};

