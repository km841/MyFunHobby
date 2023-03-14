#pragma once
#include "Component.h"

class Material;
class Mesh;
class Camera;

class MeshRenderer :
    public Component
{
public:
    MeshRenderer();
    virtual ~MeshRenderer();

    void                 Render(shared_ptr<Camera> pCamera);
                         
    void                 SetMesh(shared_ptr<Mesh> pMesh) { m_pMesh = pMesh; }
    void                 SetMaterial(shared_ptr<Material> pMaterial) { m_pMaterial = pMaterial; }

    shared_ptr<Material> GetMaterial() { return m_pMaterial; }
    shared_ptr<Mesh>     GetMesh() { return m_pMesh; }

private:
    shared_ptr<Material> m_pMaterial;
    shared_ptr<Mesh>     m_pMesh;
};

