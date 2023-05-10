#pragma once
#include "MonoBehaviour.h"
class Player;
class DarkMirrorReflectionScript :
    public MonoBehaviour
{
public:
    DarkMirrorReflectionScript(shared_ptr<Player> pPlayer);
    virtual ~DarkMirrorReflectionScript();

public:
    virtual void LateUpdate();

private:
    weak_ptr<Player> m_pPlayer;
};

