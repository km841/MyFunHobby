#pragma once
#include "MonoBehaviour.h"
class Player;
class PlayerHealthBarShowScript :
    public MonoBehaviour
{
public:
    PlayerHealthBarShowScript(shared_ptr<Player> pPlayer);
    virtual ~PlayerHealthBarShowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
};

