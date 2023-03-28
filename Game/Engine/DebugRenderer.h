#pragma once
#include "Component.h"

class Material;
class Mesh;
class Camera;

class DebugRenderer :
    public Component
{
public:
    DebugRenderer();
    ~DebugRenderer();

public:
                void                 Render(shared_ptr<Camera> pCamera);

    FORCEINLINE void                 SetMaterial(shared_ptr<Material> pMaterial) { m_pMaterial = pMaterial; }
    FORCEINLINE shared_ptr<Material> GetMaterial() const                         { return m_pMaterial; }

    FORCEINLINE void                 SetMesh(shared_ptr<Mesh> pMesh)             { m_pMesh = pMesh; }
    FORCEINLINE shared_ptr<Mesh>     GetMesh()     const                         { return m_pMesh; }

private:
    shared_ptr<Material> m_pMaterial;
    shared_ptr<Mesh>     m_pMesh;
};

