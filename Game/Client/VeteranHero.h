#pragma once
#include "Monster.h"
class LocalEffect;
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

	bool IsGround() { return m_bGroundFlag; }

public:
	void CreateStingerSlashEffectAndAddedToScene();

public:
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

public:
	void SetStingerEffectState(bool bState);

private:
	void CreateStingerEffectAndAddedToScene();

private:
	bool m_bLandingFlag;
	bool m_bLandingChecked;
	bool m_bGroundFlag;

	weak_ptr<LocalEffect> m_pStingerEffect;
};

