#pragma once
#include "PlayerProjectile.h"
class LittleBone;
class LittleBoneHead :
    public PlayerProjectile
{
public:
    LittleBoneHead();
    virtual ~LittleBoneHead();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

public:
    void SetThrowVelocity(const Vec3& vVelocity) { m_vVelocity = vVelocity; }

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) override;
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) override;

    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) override;
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) override;

private:
    weak_ptr<LittleBone> m_pLittleBone;
    Vec3 m_vVelocity;

    bool m_bTouch;
};

