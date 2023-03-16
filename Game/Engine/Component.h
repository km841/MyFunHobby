#pragma once
#include "Object.h"

enum class COMPONENT_TYPE : uint8
{
	TRANSFORM,
	CONTROLLER,
    DEBUG_RENDERER,
	MESH_RENDERER,
	RIGIDBODY,
	CAMERA,
	PHYSICAL,
	COLLIDER,
	LIGHT,
	// ...
	MONO_BEHAVIOUR,
	END,
};

enum class ACTOR_TYPE
{
	STATIC,
	DYNAMIC,
	KINEMATIC,
	CHARACTER,
	END,
};

enum class GEOMETRY_TYPE
{
    BOX,
    CAPSULE,
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
class Controller;
class Collider;
class RigidBody;
class Physical;
class Camera;

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
	shared_ptr<Controller>			GetController();
	shared_ptr<RigidBody>			GetRigidBody();
	shared_ptr<Physical>			GetPhysical();
    shared_ptr<Camera>              GetCamera();

	COMPONENT_TYPE GetType() { return m_eType; }

private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> pGameObject) { m_pGameObject = pGameObject; }

protected:
	COMPONENT_TYPE		 m_eType;
	weak_ptr<GameObject> m_pGameObject;
};

