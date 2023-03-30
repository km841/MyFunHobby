#pragma once
#include "GameObject.h"
class AfterImage :
    public GameObject
{
public:
    AfterImage();
    virtual ~AfterImage();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();


public:
    FORCEINLINE void Show()      { m_bShowTrigger = true; }
    FORCEINLINE void Check()     { m_bShowTrigger = false; }
    FORCEINLINE bool IsTrigger() { return m_bShowTrigger; }

private:
    bool m_bShowTrigger;

private:
    DECLARE_POOL(AfterImage);
};

