#pragma once
#include "HUD.h"
class EndingHUD :
    public HUD
{
public:
    EndingHUD();
    virtual ~EndingHUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action() override;

private:
    Timer m_tStayTimer;
    Timer m_tCommentTimer;
    Timer m_tCommentStayTimer;
    bool m_bAudioStart;
};

