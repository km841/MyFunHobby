#pragma once
#include "MonoBehaviour.h"
class Monster;
class BossHPScript :
    public MonoBehaviour
{
public:
    BossHPScript(shared_ptr<Monster> pMonster);
    virtual ~BossHPScript();

public:
    void LateUpdate();

private:
    weak_ptr<Monster> m_pBoss;

};

