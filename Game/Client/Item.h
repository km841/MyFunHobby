#pragma once
#include "Object.h"
class Item :
    public Object
{
public:
    Item(const ItemInfo& itemInfo);
    virtual ~Item();

public:
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();

private:
    ItemInfo m_ItemInfo;
};

