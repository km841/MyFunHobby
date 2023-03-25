#include "pch.h"
#include "Texture.h"
#include "Engine.h"

Texture::Texture()
	: Object(OBJECT_TYPE::TEXTURE)
	, m_eType{}
{
}

Texture::~Texture()
{
}

void Texture::Load(const wstring& szPath)
{
	wstring ext = fs::path(szPath).extension();

	if (ext == L".dds" || ext == L".DDS")
		LoadFromDDSFile(szPath.c_str(), DDS_FLAGS_NONE, nullptr, m_scratchImage);
	else if (ext == L".tga" || ext == L".TGA")
		LoadFromTGAFile(szPath.c_str(), nullptr, m_scratchImage);
	else // png, jpg, jpeg, bmp
		LoadFromWICFile(szPath.c_str(), WIC_FLAGS_NONE, nullptr, m_scratchImage);

	CreateShaderResourceView(
		DEVICE.Get(),
		m_scratchImage.GetImages(),
		m_scratchImage.GetImageCount(),
		m_scratchImage.GetMetadata(),
		m_pSRV.GetAddressOf());

	m_pSRV->GetResource(reinterpret_cast<ID3D11Resource**>(m_pTexture.GetAddressOf()));
	m_szName = szPath;
	m_vTexSize = Vec3(static_cast<float>(m_scratchImage.GetMetadata().width), static_cast<float>(m_scratchImage.GetMetadata().height), 1.f);
}

void Texture::Create(uint32 eType, uint32 iWidth, uint32 iHeight)
{
	D3D11_TEXTURE2D_DESC td = { 0 };
	m_vTexSize = Vec3(static_cast<float>(iWidth), static_cast<float>(iHeight), 1.f);
	
	td.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	td.CPUAccessFlags = 0;
	td.Width = iWidth;
	td.Height = iHeight;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.BindFlags = eType;

	if (eType & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		td.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	else
		td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	
	HRESULT hr = DEVICE->CreateTexture2D(&td, nullptr, m_pTexture.GetAddressOf());
	assert(SUCCEEDED(hr));

	CreateFromTexture(eType, m_pTexture);
}

void Texture::CreateFromTexture(uint32 eType, ComPtr<ID3D11Texture2D> pTexture)
{
	m_eType = eType;
	m_pTexture = pTexture;

	D3D11_TEXTURE2D_DESC td = {};
	m_pTexture->GetDesc(&td);

	if (m_eType & D3D11_BIND_RENDER_TARGET)
	{
		HRESULT hr = DEVICE->CreateRenderTargetView(pTexture.Get(), nullptr, m_pRTV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	if (m_eType & D3D11_BIND_SHADER_RESOURCE)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
		sd.Format = td.Format;
		sd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		sd.Texture2D.MipLevels = 1;

		HRESULT hr = DEVICE->CreateShaderResourceView(pTexture.Get(), &sd, m_pSRV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	if (m_eType & D3D11_BIND_DEPTH_STENCIL)
	{
		HRESULT hr = DEVICE->CreateDepthStencilView(pTexture.Get(), nullptr, m_pDSV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	if (m_eType & D3D11_BIND_UNORDERED_ACCESS)	
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
		ud.Format = td.Format;
		ud.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;
		HRESULT hr = DEVICE->CreateUnorderedAccessView(pTexture.Get(), nullptr, m_pUAV.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
}
