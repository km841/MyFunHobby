#pragma once
#include "Interface.h"
class UI :
    public Interface
{
public:
    UI();
    virtual ~UI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:

private:


};

