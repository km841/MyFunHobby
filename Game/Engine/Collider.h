#pragma once
#include "Component.h"

class ContactCallback;

class Collider :
      public Component
{
public:
    Collider();
    virtual ~Collider();

public:
    virtual void Awake() override;
    virtual void FinalUpdate() override;
    virtual void Render() override;

    virtual void OnCollision();

private:
    void CreateDebugGeometry(shared_ptr<Geometries> pGeometries);
    void CreateDebugBox(Vec3 vHalfSize);
    void CreateDebugCapsule(float fRadius, float fHalfHeight);

public:
    ContactCallback* m_pCallback;
};

