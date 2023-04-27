#pragma once
#include "InfoUI.h"
class ItemInfoUI :
    public InfoUI
{
public:
    ItemInfoUI();
    virtual ~ItemInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

