#pragma once
#include "GameObject.h"
class VenomFall :
    public GameObject
{
public:
    VenomFall();
    virtual ~VenomFall();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

private:
    void CreateVenomSplashAndAddedToScene();

private:
    bool m_bFinishedIntroFlag;
    bool m_bFinishedOutroFlag;
    bool m_bCreatedSplashFlag;
    Timer m_tLoopDuration;
};

