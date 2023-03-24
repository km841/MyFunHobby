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
    void Create(D3D11_BIND_FLAG eType, uint32 iWidth, uint32 iHeight);
    void CreateFromTexture(D3D11_BIND_FLAG eType, ComPtr<ID3D11Texture2D> pTexture);

public:
    Vec3 GetTexSize() { return Vec3(static_cast<float>(m_scratchImage.GetMetadata().width), static_cast<float>(m_scratchImage.GetMetadata().height), 1.f); }

public:

    ComPtr<ID3D11Texture2D>           GetTex2D() { return m_pTexture; }

    ComPtr<ID3D11RenderTargetView>    GetRTV()   { return m_pRTV; }
    ComPtr<ID3D11ShaderResourceView>  GetSRV()   { return m_pSRV; }
    ComPtr<ID3D11DepthStencilView>    GetDSV()   { return m_pDSV; }
    ComPtr<ID3D11UnorderedAccessView> GetUAV()   { return m_pUAV; }

private:
    D3D11_BIND_FLAG                     m_eType;

    ScratchImage                        m_scratchImage;
    ComPtr<ID3D11Texture2D>             m_pTexture;

    ComPtr<ID3D11RenderTargetView>      m_pRTV;
    ComPtr<ID3D11ShaderResourceView>    m_pSRV;
    ComPtr<ID3D11DepthStencilView>      m_pDSV;
    ComPtr<ID3D11UnorderedAccessView>   m_pUAV;
};

