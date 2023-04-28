#pragma once
#include "UI.h"
#include "InfoUI.h"

class InventoryUI;
class DetailInfoUI :
    public UI
{
public:
    friend class InventoryUI;
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
    void DrawSkulInfo();
    void DrawItemInfo();
    void DrawArtifactInfo();
    void DrawDarkAbilInfo();

    void SetSkulDetailTexture();

private:
    DetailInfo m_DetailInfo;
    weak_ptr<InventoryUI> m_pInventoryUI;

};

