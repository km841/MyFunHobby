#pragma once
#include "Component.h"
class Movement :
    public Component
{
public:
    Movement();
    virtual ~Movement();

    virtual void Awake() override;
    virtual void FinalUpdate() override;

public:
    void Move(const Vec3& vVelocity);

private:

};

