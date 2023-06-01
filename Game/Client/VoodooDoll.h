#pragma once
#include "Item.h"
class VoodooDoll :
    public Item
{
public:
    VoodooDoll(const ItemInfo& itemInfo);
    virtual ~VoodooDoll();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

