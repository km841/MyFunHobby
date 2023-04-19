#pragma once
#include "MonoBehaviour.h"
class MonsterHPHUD;
class MonsterHealthBarShowScript :
    public MonoBehaviour
{
public:
    explicit MonsterHealthBarShowScript(shared_ptr<MonsterHPHUD> pHealthBar);
    virtual ~MonsterHealthBarShowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<MonsterHPHUD> m_pHealthBar;
};

