#pragma once
#include "InfoUI.h"
class ItemInfoUI :
    public InfoUI
{
public:
    ItemInfoUI(ITEM_PLACE eItemPlace);
    virtual ~ItemInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void ShowDetailInfo();

private:
    ITEM_PLACE m_eItemPlace;
};

