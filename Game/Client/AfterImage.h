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
    FORCEINLINE void             SetFrameData(const FrameData& frameData) { m_FrameData = frameData; }
    FORCEINLINE const FrameData& GetFrameData() { return m_FrameData; }

private:
    FrameData m_FrameData;
};

