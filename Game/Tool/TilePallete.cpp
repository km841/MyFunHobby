#include "TilePallete.h"

TilePallete::TilePallete()
    : m_fTileSize(64.f)
    , m_fSpacing(8.f)
    , m_vWindowPos{}
    , m_iClickedTileIndex(-1)
{
    m_fTileWindowWidth = (m_fTileSize + m_fSpacing) * 4.7f;
    m_vTileWindowSize = ImVec2(m_fTileWindowWidth, std::ceil(m_vSRV.size() / 4.0f)* (m_fTileSize + m_fSpacing));
}

TilePallete::~TilePallete()
{

}

void TilePallete::Init(const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV)
{
    m_vSRV = vSRV;
	// 여러 장의 Texture를 로드한다.
}

void TilePallete::Update()
{
    //m_iClickedIndex = -1;
    ImGui::Begin("Pallete", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    if (ImGui::IsWindowFocused()) 
    {
        m_vWindowPos = ImGui::GetWindowPos();
    }

    ImGui::SetWindowSize(m_vTileWindowSize);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

    for (int i = 0; i < m_vSRV.size(); ++i) {
        ImGui::PushID(i);
        ImGui::ImageButton(m_vSRV[i].Get(), ImVec2(m_fTileSize, m_fTileSize));

        if (ImGui::IsItemClicked()) 
        {
            m_iClickedTileIndex = i;
        }

        ImGui::PopID();
        if ((i + 1) % 4 != 0) 
        {
            ImGui::SameLine(0.0f, m_fSpacing);
        }
    }

    if (ImGui::IsWindowFocused()) {
        ImVec2 vDelta = ImVec2(ImGui::GetWindowPos().x - m_vWindowPos.x, ImGui::GetWindowPos().y - m_vWindowPos.y);
        for (int i = 0; i < m_vSRV.size(); ++i) {
            ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + vDelta.x, ImGui::GetCursorPos().y + vDelta.y));
        }
    }

    ImGui::End();
}