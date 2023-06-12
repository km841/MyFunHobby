#pragma once
#include "MonoBehaviour.h"
class ChimeraGrabScript :
    public MonoBehaviour
{
public:
    ChimeraGrabScript();
    virtual ~ChimeraGrabScript();

public:
    virtual void LateUpdate() override;
   
private:
    void CreateWarningSignAndAddedToScene();
    void CreateFallingObjectAndAddedToScene();

private:
    bool m_bCheckedBegin;
    bool m_bCheckedSkill;
};

