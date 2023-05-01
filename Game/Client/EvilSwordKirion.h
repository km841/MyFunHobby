#pragma once
#include "Item.h"
class EvilSwordKirion :
    public Item
{
public:
    EvilSwordKirion(const ItemInfo& itemInfo);
    virtual ~EvilSwordKirion();

public:
    virtual void Awake() override;
    virtual void Start() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void FinalUpdate() override;

    virtual void ActiveMethodWhenHitTiming() override;
    virtual void ActiveMethodWhenDashTiming() override;

private:
    void CreateSlashEffectAndAddedToScene();
    void CreateDashEffectAndAddedToScene();

    float m_fDepthValue;
};

