#pragma once
#include "MonoBehaviour.h"
class Player;
class BackgroundMoveScript :
    public MonoBehaviour
{
public:
    explicit BackgroundMoveScript(shared_ptr<Player> pPlayer);
    virtual ~BackgroundMoveScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
};

