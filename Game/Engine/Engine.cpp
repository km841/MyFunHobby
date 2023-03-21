// Engine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//

#include "pch.h"
#include "Engine.h"
#include "Resources.h"
#include "Scenes.h"
#include "Timer.h"
#include "Input.h"
#include "Physics.h"
#include "Player.h"
#include "EventManager.h"
#include "CollisionManager.h"

void Engine::Init(const WindowInfo& wInfo)
{
	m_Window = wInfo;
	m_Viewport = { 0, 0,
		static_cast<FLOAT>(m_Window.iWidth),
		static_cast<FLOAT>(m_Window.iHeight),
		0.0f,
		1.0f
	};

	m_ScissorRect = CD3D11_RECT(0, 0, m_Window.iWidth, m_Window.iHeight);
	ResizeWindow(m_Window.iWidth, m_Window.iHeight);

	m_pDevice = make_shared<Device>();
	m_pContext = make_shared<Context>();
	m_pSwapChain = make_shared<SwapChain>();
	m_pPhysics = make_shared<Physics>();
	m_pUtility = make_shared<Utility>();

	ComPtr<ID3D11Device> pDevice;
	ComPtr<ID3D11DeviceContext> pContext;
#pragma region CreateDevice
	{
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(DEBUG_BUILD)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
			0, creationFlags,
			featureLevels, ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION, &pDevice,
			0, &pContext);
		if (FAILED(hResult)) {
			MessageBoxA(0, "D3D11CreateDevice() failed", "Fatal Error", MB_OK);
			return;
		}
	}

	m_pDevice->Init(pDevice);
	m_pContext->Init(pContext);
	m_pSwapChain->Init(m_Window, m_pDevice->GetDevice(), m_pDevice->GetDXGI());
	m_pPhysics->Init();
	m_pUtility->Init(pDevice, pContext);
	
	CreateRenderTargetGroups();
	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(TransformParams));
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams));

	GET_SINGLE(Resources)->Init();
	GET_SINGLE(Scenes)->Init();
	GET_SINGLE(Timer)->Init();
	GET_SINGLE(Input)->Init(m_Window.hHwnd);
}

void Engine::Update()
{
	// ImGui Update

	GET_SINGLE(Input)->Update();
	GET_SINGLE(Timer)->Update();
	GET_SINGLE(Scenes)->Update();
	GET_SINGLE(CollisionManager)->Update();
	
	m_pPhysics->Update();

	ShowFPS();
}

void Engine::Render()
{
	RenderBegin();
	GET_SINGLE(Scenes)->Render();
	RenderEnd();
}


void Engine::FinalUpdate()
{

}

void Engine::RenderBegin()
{
	CONTEXT->RSSetViewports(1, &m_Viewport);
	CONTEXT->RSSetScissorRects(1, &m_ScissorRect);
}

void Engine::RenderEnd()
{
	m_pSwapChain->Present();
	GET_SINGLE(EventManager)->ProcessEvents();
}

void Engine::Destroy()
{
	FreeLibrary(m_hModule);
}

void Engine::ShowFPS()
{
	uint32 fps = GET_SINGLE(Timer)->GetFPS();

	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);

	::SetWindowText(m_Window.hHwnd, text);
}


void Engine::ResizeWindow(int32 iWidth, int32 iHeight)
{
	m_Window.iWidth = iWidth;
	m_Window.iHeight = iHeight;

	RECT rRect = { 0, 0, iWidth, iHeight };
	AdjustWindowRect(&rRect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_Window.hHwnd, 0, 0, 0, iWidth, iHeight, 0);
}

void Engine::CreateRenderTargetGroups()
{
	shared_ptr<Texture> pDepthStencilTexture = 
		GET_SINGLE(Resources)->CreateTexture(L"DepthStencil", TEXTURE_TYPE::DEPTH_STENCIL, m_Window.iWidth, m_Window.iHeight);

	float clearColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

	std::vector<RenderTarget> vRenderTargetVec(SWAP_CHAIN_BUFFER_COUNT);
	for (uint32 i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i)
	{
		wstring name = L"SwapChainTarget_" + std::to_wstring(i);
		ComPtr<ID3D11Texture2D> pResource = {};

		HRESULT hr = m_pSwapChain->GetSwapChain()->GetBuffer(i, IID_PPV_ARGS(&pResource));
		assert(SUCCEEDED(hr));

		vRenderTargetVec[i].pTarget = GET_SINGLE(Resources)->CreateTextureFromResource(name, TEXTURE_TYPE::RENDER_TARGET, pResource);
		memcpy(vRenderTargetVec[i].fClearColors, clearColor, sizeof(float) * ARRAYSIZE(clearColor));
	}

	m_arrRTGroups[static_cast<uint8>(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)] = make_shared<RenderTargetGroup>();
	m_arrRTGroups[static_cast<uint8>(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)]->Create(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN, vRenderTargetVec, pDepthStencilTexture);
}

void Engine::CreateConstantBuffer(CBV_REGISTER eReg, uint32 iSize)
{
	uint8 iIndex = static_cast<uint8>(eReg);
	if (CBV_REGISTER_COUNT <= iIndex)
		assert(nullptr);

	m_arrCBGroups[iIndex] = make_shared<ConstantBuffer>();
	m_arrCBGroups[iIndex]->Create(eReg, iSize);
}
