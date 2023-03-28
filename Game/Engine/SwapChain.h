#pragma once
class SwapChain
{
public:
	SwapChain();
	~SwapChain();

public:
	void									   Init(const WindowInfo& wInfo, ComPtr<ID3D11Device> pDevice, ComPtr<IDXGIFactory> pDxgi);
	void									   Present();
	void									   CreateSwapChain(const WindowInfo& wInfo, ComPtr<ID3D11Device> pDevice, ComPtr<IDXGIFactory> pDxgi);
	void									   CreateRTV();

	FORCEINLINE ComPtr<IDXGISwapChain>		   GetSwapChain() const { return m_pSwapChain; }
	FORCEINLINE ComPtr<ID3D11RenderTargetView> GetRTV()		  const { return m_pRTV; }
	
private:
	ComPtr<IDXGISwapChain>		   m_pSwapChain;
	ComPtr<ID3D11RenderTargetView> m_pRTV;

};

