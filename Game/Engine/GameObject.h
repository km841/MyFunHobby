#pragma once
#include "Object.h"
#include "Component.h"

class DebugRenderer;
class MeshRenderer;
class Transform;
class Camera;
class MonoBehaviour;
class Collider;
class RigidBody;
class Physical;
class Animator;
class Movement;
class Light;
class AI;
class ParticleSystem;
class SoundListener;
class SoundSource;

using CollisionInfo = std::pair<COLLISION_SIDE, float>;
class GameObject :
    public Object
    , public std::enable_shared_from_this<GameObject>
{
public:
    GameObject(LAYER_TYPE eLayerType);
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
    shared_ptr<Camera>          GetCamera();
    shared_ptr<Animator>        GetAnimator();
    shared_ptr<Movement>        GetMovement();
    shared_ptr<Light>           GetLight();
    shared_ptr<AI>              GetAI();
    shared_ptr<ParticleSystem>  GetParticleSystem();
    shared_ptr<SoundListener>   GetSoundListener();
    shared_ptr<SoundSource>     GetSoundSource();

    void AddComponent(shared_ptr<Component> pComponent);
    void RemoveComponent(COMPONENT_TYPE eComponentType);

public:
    virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject) {}
    virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject) {}

    virtual void OnTriggerEnter(shared_ptr<GameObject> pGameObject) {}
    virtual void OnTriggerExit(shared_ptr<GameObject> pGameObject) {}

    virtual void Disable() { m_bDisable = true;  }
    virtual void Enable()  { m_bDisable = false; }

public:
    FORCEINLINE OBJECT_LEVEL_TYPE GetLevelType()                     { return m_eLevelType; }
    FORCEINLINE LAYER_TYPE        GetLayerType()                     { return m_eLayerType; }
    FORCEINLINE DIRECTION         GetDirection()                     { return m_eDirection; }
    FORCEINLINE void              SetDirection(DIRECTION eDirection) { m_eDirection = eDirection; }

    FORCEINLINE Status*           GetStatus()                        { return &m_Status; }
   
    FORCEINLINE bool              IsEnable()                         { return !m_bDisable; }
    FORCEINLINE bool              IsDisable()                        { return m_bDisable; }
    FORCEINLINE void              FlipState()                        { m_bDisable = (m_bDisable + 1) % 2; }
                                  
    FORCEINLINE bool              IsFrustum()                        { return m_bCheckFrustum; }
    FORCEINLINE void              SetFrustum(bool bCheckFrustum)     { m_bCheckFrustum = bCheckFrustum; }

    FORCEINLINE bool              IsAwake()                          { return m_bAwake; }

    void Release();
    virtual void ReturnToPool() {}
    virtual void Init(int32 iEnum) { }

    void ReorganizePosition();
    void ReorganizeVerticalPosition();
    bool DoesTileExistInDirection(DIRECTION eDirection, float fDistance);

protected:
    DIRECTION                                                m_eDirection;
    LAYER_TYPE                                               m_eLayerType;
    OBJECT_LEVEL_TYPE                                        m_eLevelType;
    Status						                             m_Status;

private:
    std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_arrComponents;
    std::vector<shared_ptr<MonoBehaviour>>                   m_vScripts;
    bool                                                     m_bDisable;
    bool                                                     m_bCheckFrustum;
    bool                                                     m_bAwake;
};

