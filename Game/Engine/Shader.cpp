#include "pch.h"
#include "Shader.h"
#include "Engine.h"

Shader::Shader()
	:Object(OBJECT_TYPE::SHADER)
{
}

Shader::~Shader()
{
}

void Shader::Load(const wstring& szPath)
{
}

void Shader::CreateGraphicsShader(const wstring& szPath, ShaderInfo shaderInfo, ShaderArg shaderArg)
{
	m_shaderInfo = shaderInfo;

	CreateVertexShader(szPath, shaderArg.szVSFuncName, "vs_5_0");
	CreatePixelShader(szPath, shaderArg.szPSFuncName, "ps_5_0");

	if (!shaderArg.szGSFuncName.empty())
		CreateGeometryShader(szPath, shaderArg.szGSFuncName, "gs_5_0");

	CreateSampler();

	D3D11_INPUT_ELEMENT_DESC inputLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	DEVICE->CreateInputLayout(inputLayoutDesc, ARRAYSIZE(inputLayoutDesc), m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), &m_pInputLayout);

#pragma region DepthStencilState
	{
		D3D11_DEPTH_STENCIL_DESC dsd = {};
		switch (shaderInfo.eDepthStencilType)
		{
		case DEPTH_STENCIL_TYPE::LESS:
			dsd.DepthEnable = TRUE;
			dsd.DepthFunc = D3D11_COMPARISON_LESS;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			break;

		case DEPTH_STENCIL_TYPE::LESS_EQUAL:
			dsd.DepthEnable = TRUE;
			dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			break;

		case DEPTH_STENCIL_TYPE::GREATER:
			dsd.DepthEnable = TRUE;
			dsd.DepthFunc = D3D11_COMPARISON_GREATER;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			break;

		case DEPTH_STENCIL_TYPE::GREATER_EQUAL:
			dsd.DepthEnable = TRUE;
			dsd.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			break;

		case DEPTH_STENCIL_TYPE::LESS_NO_WRITE:
			dsd.DepthEnable = TRUE;
			dsd.DepthFunc = D3D11_COMPARISON_LESS;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
			break;

		case DEPTH_STENCIL_TYPE::NO_DEPTH_TEST:
			dsd.DepthEnable = FALSE;
			dsd.DepthFunc = D3D11_COMPARISON_LESS;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
			break;

		case DEPTH_STENCIL_TYPE::NO_DEPTH_TEST_NO_WRITE:
			dsd.DepthEnable = FALSE;
			dsd.DepthFunc = D3D11_COMPARISON_LESS;
			dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
			break;
		}

		DEVICE->CreateDepthStencilState(&dsd, m_pDepthStencilState.GetAddressOf());
	}
#pragma endregion

#pragma region RasterizerState
	{
		D3D11_RASTERIZER_DESC rd = {};

		switch (shaderInfo.eRasterizerType)
		{
		case RASTERIZER_TYPE::CULL_BACK:
			rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
			break;

		case RASTERIZER_TYPE::CULL_FRONT:
			rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
			break;

		case RASTERIZER_TYPE::CULL_NONE:
			rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
			break;

		case RASTERIZER_TYPE::WIREFRAME:
			rd.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
			rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
			break;
		}

		DEVICE->CreateRasterizerState(&rd, m_pRasterizerState.GetAddressOf());
	}
#pragma endregion

#pragma region BlendState
	{
		D3D11_BLEND_DESC bs = {};

		switch (shaderInfo.eBlendType)
		{
		case BLEND_TYPE::DEFAULT:
			bs.AlphaToCoverageEnable = FALSE;
			bs.IndependentBlendEnable = FALSE;
			bs.RenderTarget[0].BlendEnable = TRUE;
			bs.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			bs.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			break;

		case BLEND_TYPE::ALPHA_BLEND:
			bs.AlphaToCoverageEnable = FALSE;
			bs.IndependentBlendEnable = FALSE;
			bs.RenderTarget[0].BlendEnable = TRUE;
			bs.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			bs.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			bs.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			bs.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			bs.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			bs.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			break;

		case BLEND_TYPE::ONE_TO_ONE_BLEND:
			bs.AlphaToCoverageEnable = FALSE;
			bs.IndependentBlendEnable = FALSE;
			bs.RenderTarget[0].BlendEnable = TRUE;
			bs.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
			bs.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			bs.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
			break;
		}

		HRESULT hr = DEVICE->CreateBlendState(&bs, m_pBlendState.GetAddressOf());
	}
#pragma endregion

}

void Shader::CreateComputeShader(const wstring& szPath, const string& szName, const string& szVersion)
{
	m_shaderInfo.eShaderType = SHADER_TYPE::COMPUTE;
	CreateShader(szPath, szName, szVersion, m_pCSBlob);
	HRESULT hr = DEVICE->CreateComputeShader(m_pCSBlob->GetBufferPointer(), m_pCSBlob->GetBufferSize(), nullptr, &m_pComputeShader);
	assert(SUCCEEDED(hr));
}

void Shader::Update()
{
	if (SHADER_TYPE::COMPUTE == m_shaderInfo.eShaderType)
	{
		CONTEXT->CSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
		CONTEXT->CSSetShader(m_pComputeShader.Get(), nullptr, 0);
	}

	else
	{
		CONTEXT->VSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
		CONTEXT->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
		CONTEXT->GSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());

		CONTEXT->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
		CONTEXT->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
		CONTEXT->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);
	}


	CONTEXT->IASetPrimitiveTopology(m_shaderInfo.eTopology);
	CONTEXT->IASetInputLayout(m_pInputLayout.Get());
	CONTEXT->RSSetState(m_pRasterizerState.Get());

	CONTEXT->OMSetDepthStencilState(m_pDepthStencilState.Get(), 0);
	CONTEXT->OMSetBlendState(m_pBlendState.Get(), nullptr, 0xffffffff);
}

void Shader::CreateShader(const wstring& szPath, const string& szName, const string& szVersion, ComPtr<ID3DBlob>& pBlob)
{
	uint32 iCompileFlag = 0;
#ifdef _DEBUG
	iCompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = D3DCompileFromFile(szPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		szName.c_str(), szVersion.c_str(), iCompileFlag, 0, &pBlob, &m_pErrBlob);
	
	if (FAILED(hr))
	{
		const char* errorString = NULL;
		if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
			errorString = "Could not compile shader; file not found";
		else if (m_pErrBlob) {
			errorString = (const char*)m_pErrBlob->GetBufferPointer();
			m_pErrBlob->Release();
		}
		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		assert(nullptr);
	}
}

void Shader::CreateSampler()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	//samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;

	HRESULT hr = DEVICE->CreateSamplerState(&samplerDesc, m_pSamplerState.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Shader::CreateVertexShader(const wstring& szPath, const string& szName, const string& szVersion)
{
	CreateShader(szPath, szName, szVersion, m_pVSBlob);
	HRESULT hr = DEVICE->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	assert(SUCCEEDED(hr));
}

void Shader::CreatePixelShader(const wstring& szPath, const string& szName, const string& szVersion)
{
	CreateShader(szPath, szName, szVersion, m_pPSBlob);
	HRESULT hr = DEVICE->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	assert(SUCCEEDED(hr));
}

void Shader::CreateGeometryShader(const wstring& szPath, const string& szName, const string& szVersion)
{
	CreateShader(szPath, szName, szVersion, m_pGSBlob);
	HRESULT hr = DEVICE->CreateGeometryShader(m_pGSBlob->GetBufferPointer(), m_pGSBlob->GetBufferSize(), nullptr, &m_pGeometryShader);
	assert(SUCCEEDED(hr));
}
