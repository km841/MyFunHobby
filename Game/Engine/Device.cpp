#include "pch.h"
#include "Device.h"

Device::Device()
{
}

Device::~Device()
{
}

void Device::Init(ComPtr<ID3D11Device> pDevice)
{
	m_pDevice = pDevice;
	CreateDXGIFactory(IID_PPV_ARGS(&m_pDxgi));
}
