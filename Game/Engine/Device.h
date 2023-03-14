#pragma once
class Device
{

public:
	Device();
	~Device();

public:
	void Init(ComPtr<ID3D11Device> pDevice);

	ComPtr<ID3D11Device> GetDevice() { return m_pDevice; }
	ComPtr<IDXGIFactory> GetDXGI() { return m_pDxgi; }

private:
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<IDXGIFactory> m_pDxgi;
};

