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

    virtual void Enable();
    virtual void Disable();

public:
    FORCEINLINE void SetDetailInfo(const DetailInfo& detailInfo) { m_DetailInfo = detailInfo; }

private:
    void DrawSkulInfo();
    void DrawItemInfo();
    void DrawArtifactInfo();
    void DrawDarkAbilInfo();

    void CreateDetailSubUIAndAddedToScene();
    void SetSkulDetailTexture();
    void InitSkulDetailSubUI();

    void SetItemDetailTexture();
    void InitItemDetailSubUI();

private:
    DetailInfo m_DetailInfo;
    weak_ptr<InventoryUI> m_pInventoryUI;

    shared_ptr<UI> m_pVignetteUI;
    shared_ptr<UI> m_pFirstImageUI;
    shared_ptr<UI> m_pSecondImageUI;

    

};

