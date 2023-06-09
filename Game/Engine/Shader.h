#pragma once
#include "Object.h"

enum class DEPTH_STENCIL_TYPE : uint8
{
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS_NO_WRITE, // ���� �׽�Ʈ O + ���� ��� X
    NO_DEPTH_TEST, // ���� �׽�Ʈ X + ���� ��� O
    NO_DEPTH_TEST_NO_WRITE, // ���� �׽�Ʈ X + ���� ��� X
};

enum class RASTERIZER_TYPE : uint8
{
    CULL_NONE,
    CULL_FRONT,
    CULL_BACK,
    WIREFRAME,
};

enum class BLEND_TYPE : uint8
{
    DEFAULT,
    ALPHA_BLEND,
    ONE_TO_ONE_BLEND,
    END,
};

struct ShaderArg
{
    string szVSFuncName = "VS_Main";
    string szGSFuncName = "";
    string szPSFuncName = "PS_Main";
};


struct ShaderInfo
{
    ShaderInfo(SHADER_TYPE shaderType = SHADER_TYPE::FORWARD,
        DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS,
        RASTERIZER_TYPE rasterizerType = RASTERIZER_TYPE::CULL_BACK,
        BLEND_TYPE blendType = BLEND_TYPE::DEFAULT,
        D3D_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        : eShaderType(shaderType)
        , eDepthStencilType(depthStencilType)
        , eRasterizerType(rasterizerType)
        , eBlendType(blendType)
        , eTopology(topology)
    {}

    SHADER_TYPE            eShaderType;
    DEPTH_STENCIL_TYPE     eDepthStencilType;
    RASTERIZER_TYPE        eRasterizerType;
    BLEND_TYPE             eBlendType;
    D3D_PRIMITIVE_TOPOLOGY eTopology;
};

class Shader :
    public Object
{
public:
    Shader();
    virtual ~Shader();
    virtual void Load(const wstring& szPath) override;

    void CreateGraphicsShader(const wstring& szPath, ShaderInfo shaderInfo = ShaderInfo(), ShaderArg shaderArg = ShaderArg());
    void Update();

public:
    void CreateComputeShader(const wstring& szPath, const string& szName, const string& szVersion);
    void CreateVertexShader(const wstring& szPath, const string& szName, const string& szVersion);
    void CreatePixelShader(const wstring& szPath, const string& szName, const string& szVersion);
    void CreateGeometryShader(const wstring& szPath, const string& szName, const string& szVersion);

public:
    FORCEINLINE SHADER_TYPE GetShaderType() const { return m_shaderInfo.eShaderType; }

private:
    void CreateShader(const wstring& szPath, const string& szName, const string& szVersion, ComPtr<ID3DBlob>& pBlob);
    void CreateSampler();

private:
    ShaderInfo                      m_shaderInfo;

    ComPtr<ID3D11VertexShader>      m_pVertexShader;
    ComPtr<ID3D11GeometryShader>    m_pGeometryShader;
    ComPtr<ID3D11PixelShader>       m_pPixelShader;
    ComPtr<ID3D11ComputeShader>     m_pComputeShader;

    ComPtr<ID3D11InputLayout>       m_pInputLayout;
    ComPtr<ID3D11SamplerState>      m_pSamplerState;

    ComPtr<ID3D11DepthStencilState> m_pDepthStencilState;
    ComPtr<ID3D11RasterizerState>   m_pRasterizerState;
    ComPtr<ID3D11BlendState>        m_pBlendState;

    ComPtr<ID3DBlob>                m_pVSBlob;
    ComPtr<ID3DBlob>                m_pPSBlob;
    ComPtr<ID3DBlob>                m_pGSBlob;
    ComPtr<ID3DBlob>                m_pCSBlob;
    ComPtr<ID3DBlob>                m_pErrBlob;
};

