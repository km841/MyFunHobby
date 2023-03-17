#pragma once
#include "Component.h"

class RigidBody :
    public Component
{
public:
    RigidBody();
    virtual ~RigidBody();

    virtual void Awake() override;
    virtual void FinalUpdate() override;

private:

    
    
};

