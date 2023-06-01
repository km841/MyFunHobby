#pragma once
#include "Item.h"
class RavenLordsFeather :
    public Item
{
public:
    RavenLordsFeather(const ItemInfo& itemInfo);
    virtual ~RavenLordsFeather();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
};

