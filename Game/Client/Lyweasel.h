#pragma once
#include "Essence.h"
class Lyweasel :
    public Essence
{
public:
    Lyweasel(const EssenceInfo& essenceInfo);
    virtual ~Lyweasel();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();



private:

};

