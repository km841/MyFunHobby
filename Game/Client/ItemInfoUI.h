#pragma once
#include "InfoUI.h"

using ENGRAVES = std::pair<ENGRAVE, ENGRAVE>;
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

    ENGRAVES GetEngravesInMyPlace();


private:
    void ShowItemInMyPlace();

private:
    ITEM_PLACE m_eItemPlace;
};

