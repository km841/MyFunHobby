#pragma once
#include "UI.h"
class DialogueUI :
    public UI
{
public:
    DialogueUI();
    virtual ~DialogueUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:

};

