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
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:
	bool m_bLandingFlag;
	bool m_bLandingChecked;

};

