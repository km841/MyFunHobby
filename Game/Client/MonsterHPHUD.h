#pragma once
#include "MonsterHUD.h"
class MonsterHPHUD :
    public MonsterHUD
{
public:
    MonsterHPHUD(shared_ptr<Monster> pMonster);
    virtual ~MonsterHPHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    

};

