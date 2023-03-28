#pragma once
class SwapChain
{
public:
	SwapChain();
	~SwapChain();

public:
	void						   Init(const WindowInfo& wInfo, ComPtr<ID3D11Device> pDevice, ComPtr<IDXGIFactory> pDxgi);
	ComPtr<IDXGISwapChain>		   GetSwapChain() { return m_pSwapChain; }
	void						   Present();
	void						   CreateSwapChain(const WindowInfo& wInfo, ComPtr<ID3D11Device> pDevice, ComPtr<IDXGIFactory> pDxgi);
	void						   CreateRTV();

	ComPtr<ID3D11RenderTargetView> GetRTV() { return m_pRTV; }
	
private:
	ComPtr<IDXGISwapChain>		   m_pSwapChain;
	ComPtr<ID3D11RenderTargetView> m_pRTV;

};

