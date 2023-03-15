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


	m_pPallete->Init(vSRV);
}

void Tool::Update()
{
	UpdateGui();

	m_pPallete->Update();
	// Changed
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


	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hHwnd);
	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}
