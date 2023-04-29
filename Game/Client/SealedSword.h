#pragma once
#include "Item.h"
class SealedSword :
    public Item
{
public:
    SealedSword(const ItemInfo& itemInfo);
    virtual ~SealedSword();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

