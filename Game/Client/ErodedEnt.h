#pragma once
#include "Monster.h"
class LocalEffect;
class ErodedEnt :
    public Monster
{
public:
	ErodedEnt();
	virtual ~ErodedEnt();

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

	FORCEINLINE bool GetDeadFlag() { return m_bDeadFlag; }
	FORCEINLINE void SetDeadFlag(bool bDeadFlag) { m_bDeadFlag = bDeadFlag; }

public:
	virtual void ScatterParticles(const Vec3& vDir);
	virtual void ActivateDeadEvent(const Vec3& vDir);
	virtual void ActivateDeadEvent() override;

private:
	void CreateExclamationEffectAndAddedToScene();

private:
	bool m_bDeadFlag;
	weak_ptr<LocalEffect> m_pExclamation;

private:
	DECLARE_POOL(ErodedEnt);
};

