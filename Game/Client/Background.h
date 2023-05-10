#pragma once
#include "GameObject.h"
class Background :
    public GameObject
{
public:
    Background();
    virtual ~Background();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();

    void SetFollowSpeed(const Vec3& vSpeed) { m_vFollowSpeed = vSpeed; }

private:
    Vec3 m_vFollowSpeed;
    Vec3 m_vPlayerPrevPos;

};

