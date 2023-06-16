#pragma once
#include "Monster.h"
class VeteranHero :
    public Monster
{
public:
	VeteranHero();
	virtual ~VeteranHero();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);

private:
	bool m_bLandingFlag;
	bool m_bLandingChecked;

};

