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
class Animator;

class GameObject :
      public Object
    , public std::enable_shared_from_this<GameObject>
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    
    shared_ptr<Component>       GetFixedComponent(COMPONENT_TYPE eType);
    shared_ptr<Transform>       GetTransform();
    shared_ptr<MeshRenderer>    GetMeshRenderer();
    shared_ptr<Collider>        GetCollider();
    shared_ptr<RigidBody>       GetRigidBody();
    shared_ptr<Physical>        GetPhysical();
    shared_ptr<DebugRenderer>   GetDebugRenderer();
    shared_ptr<Controller>      GetController();
    shared_ptr<Camera>          GetCamera();
    shared_ptr<Animator>        GetAnimator();

    void AddComponent(shared_ptr<Component> pComponent);

    LAYER_TYPE GetLayerType()                     { return m_eLayerType; }
    DIRECTION  GetDirection()                     { return m_eDirection; }
    void       SetDirection(DIRECTION eDirection) { m_eDirection = eDirection; }

    void Disable()   { m_bDisable = true; }
    void Enable()    { m_bDisable = false; }
    bool IsEnable()  { return !m_bDisable; }
    void FlipState() { m_bDisable = (m_bDisable + 1) % 2; }
    void Release();

protected:
    DIRECTION                                                m_eDirection;
    LAYER_TYPE                                               m_eLayerType;

private:
    std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_arrComponents;
    std::vector<shared_ptr<MonoBehaviour>>                   m_vScripts;
    bool                                                     m_bDisable;

    DECLARE_POOL(GameObject);
};

