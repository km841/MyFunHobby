#pragma once
#include "Item.h"
class RingOfMoon :
    public Item
{
public:
    RingOfMoon(const ItemInfo& itemInfo);
    virtual ~RingOfMoon();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

