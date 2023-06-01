#pragma once
#include "Item.h"
class JennysChainSickle :
    public Item
{
public:
    JennysChainSickle(const ItemInfo& itemInfo);
    virtual ~JennysChainSickle();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

