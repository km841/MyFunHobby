#include "pch.h"
#include "SwapChain.h"
#include "Engine.h"

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::Init(const WindowInfo& wInfo, ComPtr<ID3D11Device> pDevice, ComPtr<IDXGIFactory> pDxgi)
{
	CreateSwapChain(wInfo, pDevice, pDxgi);
	CreateRTV();
}

void SwapChain::Present()
{
	m_pSwapChain->Present(0, 0);
}

void SwapChain::CreateSwapChain(const WindowInfo& wInfo, ComPtr<ID3D11Device> pDevice, ComPtr<IDXGIFactory> pDxgi)
{
	m_pSwapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd = {};

	sd.BufferDesc.Width = static_cast<uint32>(wInfo.iWidth);
	sd.BufferDesc.Height = static_cast<uint32>(wInfo.iHeight);
	sd.BufferDesc.RefreshRate.Numerator = 60; // 화면 갱신 비율
	sd.BufferDesc.RefreshRate.Denominator = 1; // 화면 갱신 비율
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 버퍼의 디스플레이 형식
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1; // 멀티 샘플링 Off
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT + 1; // 전면 버퍼 + 후면 버퍼
	sd.OutputWindow = wInfo.hHwnd;
	sd.Windowed = wInfo.bWindowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = pDxgi->CreateSwapChain(pDevice.Get(), &sd, &m_pSwapChain);
	assert(SUCCEEDED(hr));
}

void SwapChain::CreateRTV()
{
	ComPtr<ID3D11Texture2D> pBackBuffer;
	m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	DEVICE->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRTV);
}
