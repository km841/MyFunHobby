#pragma once
#include "Interface.h"
class Player;
class HUD :
    public Interface
{
public:
    HUD();
    virtual ~HUD();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void Action() { }

public:
    FORCEINLINE void             SetPlayer(shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
    FORCEINLINE weak_ptr<Player> GetPlayer() { return m_pPlayer; }

protected:
    weak_ptr<Player> m_pPlayer;

};

