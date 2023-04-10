#pragma once
#include "PlayerState.h"
class Player;
class GlobalEffect;
class AfterImage;
class SwapState :
    public PlayerState
{
public:
    explicit SwapState(shared_ptr<Player> pPlayer);
    virtual ~SwapState() = default;


public:
    virtual void Awake() override;
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

public:
    void CreateAndAddAfterImageToScene();
    void CreateAndAddSwapEffectToScene();
    void EnableAndInitAfterImage();
    void EnableAndInitSwapEffect();

private:
    shared_ptr<AfterImage> m_pAfterImage;
    shared_ptr<GlobalEffect> m_pSwapEffect;

};

