#pragma once
#include "Item.h"
class DemonSwordKirion :
    public Item
{
public:
    DemonSwordKirion(const ItemInfo& itemInfo);
    virtual ~DemonSwordKirion();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

