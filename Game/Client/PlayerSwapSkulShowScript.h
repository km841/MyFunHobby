#pragma once
#include "MonoBehaviour.h"
class PlayerSwapSkulShowScript :
    public MonoBehaviour
{
public:
    explicit PlayerSwapSkulShowScript();
    virtual ~PlayerSwapSkulShowScript();

private:
    void CreateSpaceKeyHUDAndAddedToScene();

public:
    virtual void LateUpdate() override;
};

