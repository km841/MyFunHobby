#pragma once
#include "InfoUI.h"
class SkulInfoUI :
    public InfoUI
{
public:
    SkulInfoUI();
    virtual ~SkulInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void ShowDetailInfo();

    void SetSkulIndex(SKUL_INDEX eSkulIndex) { m_eSkulIndex = eSkulIndex; }

private:
    SKUL_INDEX m_eSkulIndex;
};

