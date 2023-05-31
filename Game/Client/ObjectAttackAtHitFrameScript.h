#pragma once
#include "MonoBehaviour.h"
class GameObject;
class ObjectAttackAtHitFrameScript :
    public MonoBehaviour
{
public:
    ObjectAttackAtHitFrameScript(shared_ptr<GameObject> pGameObject, DAMAGE_TYPE eDamageType, float fDamage);
    virtual ~ObjectAttackAtHitFrameScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<GameObject> m_pGameObject;
    DAMAGE_TYPE m_eDamageType;
    float m_fDamage;
};

