#pragma once
#include "MonoBehaviour.h"
class LittleBone;
class ReturnHeadScript :
    public MonoBehaviour
{
public:
    ReturnHeadScript(weak_ptr<LittleBone> pLittleBone);
    virtual ~ReturnHeadScript();
    
public:
    virtual void LateUpdate() override;

private:
    weak_ptr<LittleBone> m_pLittleBone;
};

