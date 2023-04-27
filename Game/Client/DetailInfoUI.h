#pragma once
#include "UI.h"
#include "InfoUI.h"

class DetailInfoUI :
    public UI
{
public:
    DetailInfoUI();
    virtual ~DetailInfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    FORCEINLINE void SetDetailInfo(const DetailInfo& detailInfo) { m_DetailInfo = detailInfo; }

private:
    DetailInfo m_DetailInfo;
};

