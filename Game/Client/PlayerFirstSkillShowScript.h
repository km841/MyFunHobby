#pragma once
#include "MonoBehaviour.h"
class Player;
class PlayerFirstSkillShowScript :
    public MonoBehaviour
{
public:
    explicit PlayerFirstSkillShowScript(shared_ptr<Player> pPlayer);
    virtual ~PlayerFirstSkillShowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
};

