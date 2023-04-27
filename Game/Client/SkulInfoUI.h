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
};

