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
	FORCEINLINE shared_ptr<Device>				GetDevice()	const						{ return m_pDevice; }
	FORCEINLINE shared_ptr<Context>				GetContext() const						{ return m_pContext; }
	FORCEINLINE shared_ptr<SwapChain>			GetSwapChain() const					{ return m_pSwapChain; }
	FORCEINLINE shared_ptr<Physics>				GetPhysics() const						{ return m_pPhysics; }
	FORCEINLINE shared_ptr<Utility>				GetUtility() const						{ return m_pUtility; }
	FORCEINLINE shared_ptr<ConstantBuffer>		GetCB(CONSTANT_BUFFER_TYPE eType) const { return m_arrCBGroups[static_cast<uint8>(eType)]; }
	FORCEINLINE shared_ptr<RenderTargetGroup>	GetRTGroup(RENDER_TARGET_GROUP_TYPE eType) const { return m_arrRTGroups[static_cast<uint8>(eType)]; }

	FORCEINLINE int32   GetWidth()  const { return m_Window.iWidth; }
	FORCEINLINE int32   GetHeight() const { return m_Window.iHeight; }
	FORCEINLINE HWND    GetHwnd()   const { return m_Window.hHwnd; }
	FORCEINLINE HMODULE GetModule() const { return m_hModule; }

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

