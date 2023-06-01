#pragma once
#include "Item.h"
class SwordOfSun :
    public Item
{
public:
    SwordOfSun(const ItemInfo& itemInfo);
    virtual ~SwordOfSun();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

