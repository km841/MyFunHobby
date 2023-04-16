#pragma once
#include "GameObject.h"

class MonsterAI;
class Monster :
    public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	FORCEINLINE bool IsHitFlag()		{ return m_bHitFlag; }
	FORCEINLINE void FlagAsAttacked()   { m_bHitFlag = true; }
	FORCEINLINE void UnflagAsAttacked() { m_bHitFlag = false; }

	FORCEINLINE bool IsExtraHitFlag() { return m_bExtraHitFlag; }
	FORCEINLINE void FlagAsExtraAttacked() { m_bExtraHitFlag = true; }
	FORCEINLINE void UnflagAsExtraAttacked() { m_bExtraHitFlag = false; }

public:
	bool m_bHitFlag;
	bool m_bExtraHitFlag;

public:
	virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject);

private:

};

