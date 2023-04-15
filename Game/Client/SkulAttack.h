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
	
	// 애니메이션은 세팅할 때 전달
	// 스킬은 시간을 기준으로 한다면 어택은 애니메이션이 끝나는 것을 기준으로 한다.

protected:
	uint8 m_iMaxCount;
	weak_ptr<Skul> m_pSkul;
	ATTACK_ORDER m_eActiveAttackOrder;
	std::array<std::array<AttackInfo, ATTACK_ORDER_COUNT>, MAX_ENUMS> m_arrAttackInfo;
};

