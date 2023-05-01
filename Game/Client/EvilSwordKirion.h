#pragma once
#include "Item.h"
class EvilSwordKirion :
    public Item
{
public:
    EvilSwordKirion(const ItemInfo& itemInfo);
    virtual ~EvilSwordKirion();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

