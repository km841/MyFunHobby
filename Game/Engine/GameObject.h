#pragma once
#include "Object.h"
#include "Component.h"


class DebugRenderer;
class MeshRenderer;
class Transform;
class Camera;
class MonoBehaviour;
class Controller;
class Collider;
class RigidBody;
class Physical;

class GameObject :
      public Object
    , public std::enable_shared_from_this<GameObject>
{
public:
    GameObject();
    virtual ~GameObject();

    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FinalUpdate();
    
    shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE eType);
    shared_ptr<Transform> GetTransform();
    shared_ptr<MeshRenderer> GetMeshRenderer();
    shared_ptr<Collider> GetCollider();
    shared_ptr<RigidBody> GetRigidBody();
    shared_ptr<Physical> GetPhysical();
    shared_ptr<DebugRenderer> GetDebugRenderer();
    
    shared_ptr<Controller> GetController();

    shared_ptr<Camera> GetCamera();

    void AddComponent(shared_ptr<Component> pComponent);

    void SetLayerIndex(uint8 iIndex) { m_iLayerIndex = iIndex; }
    uint8 GetLayerIndex() { return m_iLayerIndex; }

private:
    uint8                                               m_iLayerIndex;
    std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_arrComponents;
    std::vector<shared_ptr<MonoBehaviour>>                   m_vScripts;

    DECLARE_POOL(GameObject);
};

