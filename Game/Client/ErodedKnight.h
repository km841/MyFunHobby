#pragma once
#include "Monster.h"
class ErodedKnight :
    public Monster
{
public:
	ErodedKnight();
	virtual ~ErodedKnight();

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

private:
	DECLARE_POOL(ErodedKnight);
};

