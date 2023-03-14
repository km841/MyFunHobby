#pragma once
#include "Component.h"

class RigidBody :
    public Component
{
public:
    RigidBody(ACTOR_TYPE eActorType);
    virtual ~RigidBody();

    virtual void Awake() override;
    virtual void FinalUpdate() override;

private:
    ACTOR_TYPE m_eActorType;
    
    
};

