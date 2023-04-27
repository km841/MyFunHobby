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
};

struct DetailInfo
{
    INFO_TYPE eInfoType;
    
    // SkulInfo
    shared_ptr<Texture> pSkulSkillFirst;
    shared_ptr<Texture> pSkulSkillSecond;

    // ItemInfo
    shared_ptr<Texture> pSetAbilFirst;
    shared_ptr<Texture> pSetAbilSecond;

    shared_ptr<Texture> pThumnail;
    wstring szName;
    wstring szComment;
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

