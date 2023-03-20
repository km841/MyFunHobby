#pragma once

#include "Device.h"
#include "Context.h"
#include "SwapChain.h"
#include "RenderTargetGroup.h"
#include "ConstantBuffer.h"
#include "Physics.h"
#include "Utility.h"

class GameObject;

class Engine
{
public:
	void Init(const WindowInfo& wInfo);
	void Update();
	void FinalUpdate();

	void Render();
	void RenderBegin();
	void RenderEnd();

	void Destroy();

	void ShowFPS();

public:
	shared_ptr<Device>				GetDevice() { return m_pDevice; }
	shared_ptr<Context>				GetContext() { return m_pContext; }
	shared_ptr<SwapChain>			GetSwapChain() { return m_pSwapChain; }
	shared_ptr<Physics>				GetPhysics() { return m_pPhysics; }
	shared_ptr<Utility>				GetUtility() { return m_pUtility; }
	shared_ptr<ConstantBuffer>		GetCB(CONSTANT_BUFFER_TYPE eType) { return m_arrCBGroups[static_cast<uint8>(eType)]; }
	shared_ptr<RenderTargetGroup>	GetRTGroup(RENDER_TARGET_GROUP_TYPE eType) { return m_arrRTGroups[static_cast<uint8>(eType)]; }

	int32   GetWidth()  { return m_Window.iWidth; }
	int32   GetHeight() { return m_Window.iHeight; }
	HWND    GetHwnd()   { return m_Window.hHwnd; }
	HMODULE GetModule() { return m_hModule; }

private:
	void ResizeWindow(int32 iWidth, int32 iHeight);
	void CreateRenderTargetGroups();
	void CreateConstantBuffer(CBV_REGISTER eReg, uint32 iSize);


private:
	WindowInfo				m_Window;
	HMODULE					m_hModule;

	D3D11_VIEWPORT			m_Viewport = {};
	D3D11_RECT				m_ScissorRect = {};

	shared_ptr<Device>		m_pDevice;
	shared_ptr<Context>		m_pContext;
	shared_ptr<SwapChain>	m_pSwapChain;
	shared_ptr<Physics>		m_pPhysics;
	shared_ptr<Utility>     m_pUtility;

	std::array<shared_ptr<ConstantBuffer>, CONSTANT_BUFFER_TYPE_COUNT>		  m_arrCBGroups;
	std::array<shared_ptr<RenderTargetGroup>, RENDER_TARGET_GROUP_TYPE_COUNT> m_arrRTGroups;
	
};

