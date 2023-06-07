#pragma once
#include "GameObject.h"
class ChimeraSprite :
    public GameObject
{
public:
    ChimeraSprite();
    virtual ~ChimeraSprite();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Destroy();
};

