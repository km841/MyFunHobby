#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
public:
    TitleScene();
    virtual ~TitleScene();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Render();

public:
    virtual void Enter();
    virtual void Exit();

private:
    shared_ptr<GameObject> m_pBackground;
    shared_ptr<GameObject> m_pLogo;

    Timer m_tStayTimer;
    float m_fAlphaValue;
    
   
};

