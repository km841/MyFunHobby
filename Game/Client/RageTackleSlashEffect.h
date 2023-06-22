#pragma once
#include "GameObject.h"

enum class SLASH_KIND : uint8
{
    A,
    B,
    C,
    D,
    E
};

class RageTackleSlashEffect :
    public GameObject
{
public:
    RageTackleSlashEffect();
    virtual ~RageTackleSlashEffect();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();


    void MonsterTakeDamageAndImpulse(const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse);

    void SetSlashKind(int32 iAlpha)
    {
        m_eSlashKind = static_cast<SLASH_KIND>('e' - iAlpha);
    }

private:
    void CreateHitEffectAndAddedScene(Vec3 vMonsterPos);

private:
    DECLARE_POOL(RageTackleSlashEffect);

private:
    SLASH_KIND m_eSlashKind;
};

