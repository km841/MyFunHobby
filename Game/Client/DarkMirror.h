#pragma once
#include "GameObject.h"
class DarkMirror :
    public GameObject
{
public:
    DarkMirror();
    virtual ~DarkMirror();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

