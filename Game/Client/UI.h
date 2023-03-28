#pragma once
#include "GameObject.h"
class UI :
    public GameObject
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

