#pragma once
class Device
{

public:
	Device();
	~Device();

public:
	void Init(ComPtr<ID3D11Device> pDevice);

	FORCEINLINE ComPtr<ID3D11Device> GetDevice() { return m_pDevice; }
	FORCEINLINE ComPtr<IDXGIFactory> GetDXGI() { return m_pDxgi; }

private:
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<IDXGIFactory> m_pDxgi;
};

