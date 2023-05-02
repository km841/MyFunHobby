#pragma once
#include "Object.h"
class Player;
class Essence :
    public Object
{
public:
    Essence(const EssenceInfo& essenceInfo);
    virtual ~Essence();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    FORCEINLINE void               SetPlayer(shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
    FORCEINLINE const EssenceInfo& GetEssenceInfo()                      { return m_EssenceInfo; }

    virtual void ActiveMethodWhenDashEnterTiming() { }

private:
    EssenceInfo m_EssenceInfo;

protected:
    weak_ptr<Player> m_pPlayer;
};

