#pragma once
#include "UI.h"

class Texture;
class DetailInfoUI;
enum class INFO_TYPE
{
    SKUL_INFO,
    ITEM_INFO,
    ARTIFACT_INFO,
    DARKABIL_INFO,
    END,
};

enum
{
    INFO_TYPE_COUNT = INFO_TYPE::END,
};

struct DetailInfo
{
    INFO_TYPE eInfoType;
    
    // SkulInfo
    SkulInfo skulInfo;

    SKILL_INDEX eTotalSkills;

    // ItemInfo
    ItemInfo itemInfo;

    shared_ptr<Texture> pVignette;
    Vec2 vVignetteOffset;
    GRADE eGrade;

    bool bUse;
};

class InfoUI :
    public UI
{
public:
    InfoUI(INFO_TYPE eInfoType);
    virtual ~InfoUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    
    virtual void Enable();
    virtual void Disable();

    virtual void ShowDetailInfo() = 0;

public:
    FORCEINLINE void SetDetailInfoUI(shared_ptr<DetailInfoUI> pDetailInfoUI) { m_pDetailInfoUI = pDetailInfoUI; }

public:
    static weak_ptr<InfoUI> GetSelectedInfoUI() { return s_pSelectedInfoUI; }

private:
    void UpdateSelectedUI();

protected:
    static weak_ptr<InfoUI> s_pSelectedInfoUI;

    INFO_TYPE m_eInfoType;
    shared_ptr<Texture> m_pDeselectedTexture;
    shared_ptr<Texture> m_pSelectedTexture;

    DetailInfo m_DetailInfo;
    weak_ptr<DetailInfoUI> m_pDetailInfoUI;

};

