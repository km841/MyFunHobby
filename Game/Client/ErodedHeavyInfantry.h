#pragma once
#include "Monster.h"
class LocalEffect;
class ErodedHeavyInfantry :
    public Monster
{
public:
	ErodedHeavyInfantry();
	virtual ~ErodedHeavyInfantry();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

public:
	virtual void ScatterParticles(const Vec3& vDir);
	virtual void ActivateDeadEvent(const Vec3& vDir);
	virtual void ActivateDeadEvent() override;

	FORCEINLINE int32 GetAttackCount()      { return m_iAttackCount; }
	FORCEINLINE void  IncreaseAttackCount() { m_iAttackCount++; }
	FORCEINLINE void  ClearAttackCount()	{ m_iAttackCount = 0; }

	FORCEINLINE weak_ptr<LocalEffect> GetExclamationEffect() { return m_pExclamation; }

private:
	void CreateExclamationEffectAndAddedToScene();

private:
	int32 m_iAttackCount;
	weak_ptr<LocalEffect> m_pExclamation;

private:
	DECLARE_POOL(ErodedHeavyInfantry);
};

