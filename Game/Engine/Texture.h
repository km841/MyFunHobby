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
    FORCEINLINE Vec3 GetTexSize() { return m_vTexSize; }

public:
    FORCEINLINE ComPtr<ID3D11Texture2D>           GetTex2D() const { return m_pTexture; }
    FORCEINLINE ComPtr<ID3D11RenderTargetView>    GetRTV()   const { return m_pRTV; }
    FORCEINLINE ComPtr<ID3D11ShaderResourceView>  GetSRV()   const { return m_pSRV; }
    FORCEINLINE ComPtr<ID3D11DepthStencilView>    GetDSV()   const { return m_pDSV; }
    FORCEINLINE ComPtr<ID3D11UnorderedAccessView> GetUAV()   const { return m_pUAV; }

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

