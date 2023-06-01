#include "Tool.h"
#include "MapEditor.h"
#include "AnimationEditor.h"


Tool::Tool()
{
}

Tool::~Tool()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Tool::Init(HWND hHwnd, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const std::array<std::vector<ComPtr<ID3D11ShaderResourceView>>, SRV_KIND_COUNT>& vSRV)
{
	InitGui(hHwnd, pDevice, pContext);

	m_pMapEditor = make_shared<MapEditor>();
	m_pAnimEditor = make_shared<AnimationEditor>();

	m_pMapEditor->Init(vSRV);
}

void Tool::Update()
{
	UpdateGui();

	m_pAnimEditor->Update();
	m_pMapEditor->Update();
	// Changed
}

void Tool::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
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
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hHwnd);
	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}
