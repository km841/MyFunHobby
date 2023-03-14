#include "Tool.h"
#include "TilePallete.h"


Tool::Tool()
{
}

Tool::~Tool()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Tool::Init(HWND hHwnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV)
{
	InitGui(hHwnd, pDevice, pContext);

	m_pPallete = make_shared<TilePallete>();

	
	// ShaderResourceView로 이루어진 벡터를 전달받는다
	m_pPallete->Init(vSRV);


}

void Tool::Update()
{
	UpdateGui();

	m_pPallete->Update();
	// This Code
}

void Tool::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT Tool::DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
}

void Tool::UpdateGui()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Tool::InitGui(HWND hHwnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hHwnd);
	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}
