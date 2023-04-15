#pragma once
#include "SkulAttack.h"
class Skul;
class LittleBoneAttack :
    public SkulAttack
{
public:
    LittleBoneAttack(shared_ptr<Skul> pSkul);
    virtual ~LittleBoneAttack();

public:
    virtual void Update() override;
    virtual void Enter() override;
    virtual void Exit() override;

private:

};

