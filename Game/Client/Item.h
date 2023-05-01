#pragma once
#include "Object.h"
class Texture;
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

    FORCEINLINE const ItemInfo& GetItemInfo() { return m_ItemInfo; }

private:
    ItemInfo m_ItemInfo;
};

