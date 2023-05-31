#pragma once
#include "MonoBehaviour.h"
class PlayerClubberShowScript :
    public MonoBehaviour
{
public:
    PlayerClubberShowScript();
    virtual ~PlayerClubberShowScript();

public:
    virtual void LateUpdate() override;
};

