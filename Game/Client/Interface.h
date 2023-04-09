#pragma once
#include "GameObject.h"
class Interface :
    public GameObject
{
public:
    Interface(LAYER_TYPE eLayerType);
    virtual ~Interface();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

