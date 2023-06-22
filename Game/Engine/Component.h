#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : uint8
{
	LIGHT,
    ANIMATOR,
	TRANSFORM,
	CONTROLLER,
    DEBUG_RENDERER,
	MESH_RENDERER,
	RIGIDBODY,
    MOVEMENT,
	CAMERA,
	PHYSICAL,
	COLLIDER,
    AI,
    PARTICLE_SYSTEM,
    SOUND_LISTENER,
    SOUND_SOURCE,
	// ...
	MONO_BEHAVIOUR,
	END,
};

enum class ACTOR_TYPE
{
	STATIC,
	DYNAMIC,
	KINEMATIC,
    MONSTER_DYNAMIC,
    PROJECTILE_DYNAMIC,
	END,
};

enum class GEOMETRY_TYPE
{
    BOX,
    CAPSULE,
    SPHERE,
    PLANE,
    END,
};

struct Geometries
{
    Geometries(GEOMETRY_TYPE eGeometryType, Vec3 vBoxHalfSize)
        : eGeomType(GEOMETRY_TYPE::BOX)
    {
        if (GEOMETRY_TYPE::BOX == eGeometryType)
        {
            boxGeom = PxBoxGeometry(Conv::Vec3ToPxVec3(vBoxHalfSize));
        }
    }

    Geometries(GEOMETRY_TYPE eGeometryType, float fRadius, float fHalfHeight)
        : eGeomType(GEOMETRY_TYPE::CAPSULE)
    {
        if (GEOMETRY_TYPE::CAPSULE == eGeometryType)
        {
            capsuleGeom = PxCapsuleGeometry(fRadius, fHalfHeight);
        }
    }

    Geometries(GEOMETRY_TYPE eGeometryType, float fRadius)
        : eGeomType(GEOMETRY_TYPE::SPHERE)
    {
        if (GEOMETRY_TYPE::SPHERE == eGeometryType)
        {
            sphereGeom = PxSphereGeometry(fRadius);
        }
    }

    Geometries(GEOMETRY_TYPE eGeometryType)
        : eGeomType(GEOMETRY_TYPE::PLANE)
    {
        // RigidStatic¿œ ãö,
        if (GEOMETRY_TYPE::PLANE == eGeometryType)
        {
            planeGeom = PxPlaneGeometry();  
        }
    }

    PxBoxGeometry boxGeom;
    PxCapsuleGeometry capsuleGeom;
    PxPlaneGeometry planeGeom;
    PxSphereGeometry sphereGeom;
    GEOMETRY_TYPE eGeomType;
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1
};

class GameObject;
class Transform;
class MeshRenderer;
class DebugRenderer;
class Collider;
class RigidBody;
class Physical;
class Camera;
class Animator;
class PlayerState;
class Movement;
class Light;
class AI;
class ParticleSystem;

class Component :
    public Object
{
public:
    Component(COMPONENT_TYPE eType);
    virtual ~Component();

	virtual void Awake() { }
	virtual void Start() { }
	virtual void Update() { }
	virtual void LateUpdate() { }
	virtual void FinalUpdate() { }
	virtual void Render() { }

public:
	shared_ptr<GameObject>			GetGameObject();
	shared_ptr<Transform>			GetTransform();
    shared_ptr<DebugRenderer>       GetDebugRenderer();
	shared_ptr<MeshRenderer>		GetMeshRenderer();
	shared_ptr<RigidBody>			GetRigidBody();
	shared_ptr<Physical>			GetPhysical();
    shared_ptr<Camera>              GetCamera();
    shared_ptr<Animator>            GetAnimator();
    shared_ptr<Collider>            GetCollider();
    shared_ptr<Movement>            GetMovement();
    shared_ptr<Light>               GetLight();
    shared_ptr<AI>                  GetAI();
    shared_ptr<ParticleSystem>      GetParticleSystem();

	FORCEINLINE COMPONENT_TYPE GetType() const { return m_eType; }
    PLAYER_STATE   GetPlayerStateEnum();

private:
	friend class GameObject;
	FORCEINLINE void SetGameObject(shared_ptr<GameObject> pGameObject) { m_pGameObject = pGameObject; }

protected:
	COMPONENT_TYPE		 m_eType;
	weak_ptr<GameObject> m_pGameObject;
};

