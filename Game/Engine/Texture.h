#pragma once
#include "Object.h"

class Texture :
    public Object
{
public:
    Texture();
    virtual ~Texture();
    virtual void Load(const wstring& szPath) override;

public:
    void Create(uint32 eType, uint32 iWidth, uint32 iHeight);
    void CreateFromTexture(uint32 eType, ComPtr<ID3D11Texture2D> pTexture);

public:
    Vec3 GetTexSize() { return m_vTexSize; }

public:

    ComPtr<ID3D11Texture2D>           GetTex2D() { return m_pTexture; }

    ComPtr<ID3D11RenderTargetView>    GetRTV()   { return m_pRTV; }
    ComPtr<ID3D11ShaderResourceView>  GetSRV()   { return m_pSRV; }
    ComPtr<ID3D11DepthStencilView>    GetDSV()   { return m_pDSV; }
    ComPtr<ID3D11UnorderedAccessView> GetUAV()   { return m_pUAV; }

private:
    uint32                              m_eType;
    Vec3                                m_vTexSize;

    ScratchImage                        m_scratchImage;
    ComPtr<ID3D11Texture2D>             m_pTexture;

    ComPtr<ID3D11RenderTargetView>      m_pRTV;
    ComPtr<ID3D11ShaderResourceView>    m_pSRV;
    ComPtr<ID3D11DepthStencilView>      m_pDSV;
    ComPtr<ID3D11UnorderedAccessView>   m_pUAV;
};

