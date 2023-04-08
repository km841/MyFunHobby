#pragma once
#include "MonoBehaviour.h"
class Player;
class SkulHeadHUD;
class PlayerSkulThumnailScript :
    public MonoBehaviour
{
public:
    explicit PlayerSkulThumnailScript(shared_ptr<Player> pPlayer, shared_ptr<SkulHeadHUD> pSkulHeadHUD);
    virtual ~PlayerSkulThumnailScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
    weak_ptr<SkulHeadHUD> m_pSkulHeadHUD;
};

