#pragma once
#include "InfoUI.h"
class ArtifactInfoUI :
    public InfoUI
{
public:
    ArtifactInfoUI();
    virtual ~ArtifactInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    virtual void ShowDetailInfo();
};

