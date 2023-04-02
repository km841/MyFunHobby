#pragma once
#include "PlayerState.h"

class AfterImage;
class DashState :
    public PlayerState
{
public:
    explicit DashState(shared_ptr<Player> pPlayer);
    virtual ~DashState() = default;

public:
    virtual void Awake() override;
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;
    virtual void PlayAnimation() override;

private:
    void EnableAndInitAfterImage(weak_ptr<AfterImage> pAfterImage);
    void CreateAndAddAfterImagesToScene();

private:
    Timer m_tDuration;
    float m_fDashSpeed;
    float m_fAfterImageTimeOffset;

    std::vector<shared_ptr<AfterImage>> m_vAfterImages;
    int32 m_iAfterImageMaxCount;
};

