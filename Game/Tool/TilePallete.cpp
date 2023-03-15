#include "TilePallete.h"

TilePallete::TilePallete()
    : m_fTileSize(64.f)
    , m_fSpacing(8.f)
    , m_vWindowPos{}
    , m_iClickedTileIndex(-1)
    , m_iClickedColliderType(0)
    , m_iDrawingType(0)
    , m_iOutputType(0)
    , m_bMouseOver(false)
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
    if (ImGui::Begin("Tile Pallete", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        UpdateUIHoverState();

        if (ImGui::IsWindowFocused())
        {
            m_vWindowPos = ImGui::GetWindowPos();
        }
        ImGui::SetWindowSize(m_vTileWindowSize);

        if (ImGui::BeginTabBar("Tab"))
        {
            UpdateOptionSelection();
            UpdateTileSelection();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void TilePallete::InsertSeparator()
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
}

void TilePallete::ColliderTypeUI_Update()
{
    ImGui::BeginGroup();
    ImGui::Text("Collider Type");
    ImGui::RadioButton("None", &m_iClickedColliderType, 0);
    ImGui::RadioButton("Wall", &m_iClickedColliderType, 1);
    ImGui::RadioButton("Foothold", &m_iClickedColliderType, 2);
    ImGui::EndGroup();
}

void TilePallete::DrawingTypeUI_Update()
{
    ImGui::BeginGroup();
    ImGui::Text("Drawing Mode");
    ImGui::RadioButton("Dragging", &m_iDrawingType, 0);
    ImGui::RadioButton("Pen", &m_iDrawingType, 1);
    ImGui::EndGroup();
}

void TilePallete::TileButtonUI_Update()
{
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
}

void TilePallete::OutputTypeUI_Update()
{
    ImGui::BeginGroup();
    ImGui::Text("Output Mode");
    ImGui::RadioButton("Write", &m_iOutputType, 0);
    ImGui::RadioButton("Erase", &m_iOutputType, 1);
    ImGui::EndGroup();
}

void TilePallete::UpdateOptionSelection()
{
    if (ImGui::BeginTabItem("Option"))
    {
        ColliderTypeUI_Update();

        InsertSeparator();

        DrawingTypeUI_Update();

        InsertSeparator();

        OutputTypeUI_Update();

        ImGui::EndTabItem();
    }
}

void TilePallete::UpdateTileSelection()
{
    if (ImGui::BeginTabItem("Tile"))
    {
        TileButtonUI_Update();
        ImGui::EndTabItem();
    }
}

void TilePallete::UpdateUIHoverState()
{
    ImVec2 vPos = ImGui::GetWindowPos();
    ImVec2 vSize = ImGui::GetWindowSize();
    vSize = ImVec2(vPos.x + vSize.x, vPos.y + vSize.y);
    m_bMouseOver = ImGui::IsMouseHoveringRect(vPos, vSize);
}
