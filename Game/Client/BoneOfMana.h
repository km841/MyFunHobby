#pragma once
#include "Item.h"
class BoneOfMana :
    public Item
{
public:
    BoneOfMana(const ItemInfo& itemInfo);
    virtual ~BoneOfMana();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

