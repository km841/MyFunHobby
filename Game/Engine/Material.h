#pragma once
#include "Object.h"

class Shader;
class Texture;

class Material :
    public Object
{
public:
    Material();
    virtual ~Material();

    void PushGraphicData();
    void PushComputeData();
    void Dispatch(uint32 iCountX, uint32 iCountY, uint32 iCountZ);

    void SetShader(shared_ptr<Shader> pShader) { m_pShader = pShader; }
    void SetTexture(uint8 iIndex, shared_ptr<Texture> pTexture);
    shared_ptr<Texture> GetTexture(uint8 iIndex) { return m_pTextures[iIndex]; }

    void SetInt(uint8 iIndex, int32 iValue) { m_materialParams.SetInt(iIndex, iValue); }
    void SetFloat(uint8 iIndex, float fValue) { m_materialParams.SetFloat(iIndex, fValue); }

    void SetVec2(uint8 iIndex, Vec2 vValue) { m_materialParams.SetVec2(iIndex, vValue); }
    void SetVec3(uint8 iIndex, Vec3 vValue) { m_materialParams.SetVec3(iIndex, vValue); }
    void SetVec4(uint8 iIndex, Vec4 vValue) { m_materialParams.SetVec4(iIndex, vValue); }

    shared_ptr<Material> Clone();

    void ClearComputeData();

private:
    shared_ptr<Shader>      m_pShader;
    std::array<shared_ptr<Texture>, MATERIAL_VALUE_COUNT> m_pTextures;
    MaterialParams          m_materialParams;
    void**                  m_ppNullptr;

    
    


    

};

