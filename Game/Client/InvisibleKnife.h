#pragma once
#include "Item.h"
class InvisibleKnife :
    public Item
{
public:
    InvisibleKnife(const ItemInfo& itemInfo);
    virtual ~InvisibleKnife();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

    virtual void ActiveItemWhenMonsterHitTiming(shared_ptr<Monster> pMonster);
};

