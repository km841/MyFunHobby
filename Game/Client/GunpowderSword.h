#pragma once
#include "Item.h"
class GunpowderSword :
    public Item
{
public:
    GunpowderSword(const ItemInfo& itemInfo);
    virtual ~GunpowderSword();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

