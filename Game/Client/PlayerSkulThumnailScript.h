#pragma once
#include "MonoBehaviour.h"
class Player;
class SkulThumnailHUD;
class PlayerSkulThumnailScript :
    public MonoBehaviour
{
public:
    explicit PlayerSkulThumnailScript(shared_ptr<SkulThumnailHUD> pSkulHeadHUD);
    virtual ~PlayerSkulThumnailScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
    weak_ptr<SkulThumnailHUD> m_pSkulThumnailHUD;
};

