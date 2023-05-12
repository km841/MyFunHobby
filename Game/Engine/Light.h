#pragma once
#include "Component.h"

class Mesh;
class Material;
class Camera;

enum class LIGHT_TYPE : uint8
{
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,
};

struct LightColor
{
    Vec4 vDiffuse;
    Vec4 vAmbient;
    Vec4 vSpecular;
};

struct LightInfo
{
    LightColor Color;
    Vec4 vPosition;
    Vec4 vDirection;
    int32 eLightType;
    float fRange;
    float fAngle;
    int32 iPadding;
};

struct LightParams
{
    uint32 iLightCount;
    Vec3 vPadding;
    LightInfo Lights[50];
};

class Light :
    public Component
{
public:
    Light();
    virtual ~Light();

    virtual void FinalUpdate() override;
    void Render(shared_ptr<Camera> pCamera);
public:
    const LightInfo& GetLightInfo() { return m_LightInfo; }
    void SetLightDirection(const Vec3& vDirection) { m_LightInfo.vDirection = vDirection; }

    Vec3 GetDiffuse() { return Vec3(m_LightInfo.Color.vDiffuse.x, m_LightInfo.Color.vDiffuse.y, m_LightInfo.Color.vDiffuse.z); }

    void AddDiffuse(const Vec3& vDiffuse) { m_LightInfo.Color.vDiffuse += vDiffuse; }
    void SetDiffuse(const Vec3& vDiffuse) { m_LightInfo.Color.vDiffuse = vDiffuse; }
    void SetAmbient(const Vec3& vAmbient) { m_LightInfo.Color.vAmbient = vAmbient; }
    void SetSpecular(const Vec3& vSpecular) { m_LightInfo.Color.vSpecular = vSpecular; }
    
    void SetLightType(LIGHT_TYPE eLightType);
    void SetLightRange(float fRange) { m_LightInfo.fRange = fRange; }
    void SetLightAngle(float fAngle) { m_LightInfo.fAngle = fAngle; }

    void SetLightIndex(int8 iIndex) { m_iLightIndex = iIndex; }

    void SetLightOffset(const Vec2& vOffset) { m_vLightOffset = vOffset; }

private:
    LightInfo m_LightInfo;

    Vec2 m_vLightOffset;
    int8 m_iLightIndex;
    shared_ptr<Mesh> m_pMesh;
    shared_ptr<Material> m_pMaterial;
};

