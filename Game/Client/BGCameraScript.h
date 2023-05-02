#pragma once
#include "MonoBehaviour.h"
class Player;
class BGCameraScript :
    public MonoBehaviour
{
public:
    explicit BGCameraScript(shared_ptr<Player> pPlayer);
    virtual ~BGCameraScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
};

