#pragma once
#include "UI.h"
class InfoUI :
    public UI
{
public:
    InfoUI();
    virtual ~InfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    static weak_ptr<InfoUI> s_pSelectedInfoUI;

};

