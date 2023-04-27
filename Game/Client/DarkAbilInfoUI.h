#pragma once
#include "InfoUI.h"
class DarkAbilInfoUI :
    public InfoUI
{
public:
    DarkAbilInfoUI();
    virtual ~DarkAbilInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void ShowDetailInfo();
};

