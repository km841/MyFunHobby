#pragma once
#include "UI.h"
class InfoUI;
class DetailInfoUI;
class Engrave;
class InventoryUI :
    public UI
{
public:
    InventoryUI();
    virtual ~InventoryUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    virtual void Enable();
    virtual void Disable();

private:
    void CreateChildUIAndAddedToScene();
    void CreateSkulInfoUI();
    void CreateArtifactInfoUI();
    void CreateItemInfoUI();
    void CreateDarkAbilInfoUI();
    void CreateDetailInfoUI();
    void ShowInventorySubjectForElements();

    // About engraves
    void UpdateEngraves();
    void ShowEngraveIcons();
    void ApplyEngravesStatus();

private:
    std::vector<shared_ptr<InfoUI>> m_vSkulInfoUI;
    std::vector<shared_ptr<InfoUI>> m_vItemInfoUI;
    std::vector<shared_ptr<InfoUI>> m_vEssenceInfoUI;
    std::vector<shared_ptr<InfoUI>> m_vDarkAbilInfoUI;

    shared_ptr<DetailInfoUI> m_pDetailInfoUI;

    std::map<ENGRAVE, uint8> m_mEngraves;

    // Awake에서 Child ui를 모두 씬에 추가시킨다.
    // Child ui는 부모 ui가 enable일 때 같이 enable됨
    // 좌표계는 부모의 좌표계를 따른다
    // active된 슬롯은 스컬 또는 아이템 중 하나이며, 
    // active된 슬롯이 nullptr이 아닌 경우 해당 설명을 우측에 표시한다.
    // 표시는 적절한 위치에 텍스트와 이미지를 넣는 방식
    // 이 텍스트와 이미지는 아이템이나 스컬이 관리
    // SkulInfo = 플레이어가 보유중인 스컬에서 이미지를 가져온다.
    // ItemInfo = 플레이어가 보유중인 아이템에서 이미지를 가져온다.

};

