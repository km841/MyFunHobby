#pragma once
#include "InfoUI.h"
class EssenceInfoUI :
    public InfoUI
{
public:
    EssenceInfoUI();
    virtual ~EssenceInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void ShowDetailInfo();
    
private:
    void ShowEssenceInMyPlace();
};

