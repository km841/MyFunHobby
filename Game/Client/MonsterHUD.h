#pragma once
#include "GameObject.h"
class Monster;
class MonsterHUD :
    public GameObject
{
public:
    MonsterHUD(shared_ptr<Monster> pMonster);
    virtual ~MonsterHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    FORCEINLINE weak_ptr<Monster> GetMonster() { return m_pMonster; }

protected:
    weak_ptr<Monster> m_pMonster;
};

