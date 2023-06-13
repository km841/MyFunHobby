#pragma once
#include "MonoBehaviour.h"
class ChimeraBreathScript :
    public MonoBehaviour
{
public:
    ChimeraBreathScript();
    virtual ~ChimeraBreathScript();

public:
    virtual void LateUpdate() override;

private:
    void CreateBreathFireAndAddedToScene();
    void CreateBreathProjectileAddedToScene(float fRadian);

private:
    bool m_bChecked;
    Timer m_tBreathTick;

};

