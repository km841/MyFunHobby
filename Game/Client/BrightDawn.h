#pragma once
#include "Item.h"
class BrightDawn :
    public Item
{
public:
    BrightDawn(const ItemInfo& itemInfo);
    virtual ~BrightDawn();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

