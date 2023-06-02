#pragma once
#include "Item.h"
class ForbiddenSword :
      public Item
    , public std::enable_shared_from_this<ForbiddenSword>
{
public:
    ForbiddenSword(const ItemInfo& itemInfo);
    virtual ~ForbiddenSword();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

    virtual void ActiveItemWhenMonsterKillTiming();
};

