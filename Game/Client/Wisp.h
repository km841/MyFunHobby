#pragma once
#include "Essence.h"
class Wisp :
    public Essence
{
public:
    Wisp(const EssenceInfo& essenceInfo);
    virtual ~Wisp();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
};

