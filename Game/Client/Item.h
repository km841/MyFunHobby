#pragma once
#include "Object.h"
class Texture;
class Player;
class Item :
    public Object
{
public:
    Item(const ItemInfo& itemInfo);
    virtual ~Item();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    FORCEINLINE const ItemInfo& GetItemInfo()                         { return m_ItemInfo; }
    FORCEINLINE void            SetPlayer(shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

    virtual void ActiveMethodWhenHitTiming() { }
    virtual void ActiveMethodWhenDashTiming() { }
    virtual void ActiveItemWhenJumpAttackEnterTiming() { }
    virtual void ActiveItemWhenMonsterKillTiming() { }

public:
    static std::vector<ITEM_KIND> GetItemKindsOfGrade(GRADE eGrade);
    static wstring GetItemKindToDropItemPath(ITEM_KIND eItemKind);

private:
    ItemInfo m_ItemInfo;

protected:
    weak_ptr<Player> m_pPlayer;
};

