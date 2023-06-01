#pragma once
#include "Item.h"
class ThiefsBlackIronDaggers :
    public Item
{
public:
    ThiefsBlackIronDaggers(const ItemInfo& itemInfo);
    virtual ~ThiefsBlackIronDaggers();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

