#pragma once
#include "Item.h"
class ForbiddenSword :
    public Item
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
};

