#include "MapEditor.h"

MapEditor::MapEditor()
    : m_fTileSize(64.f)
    , m_fSpacing(8.f)
    , m_vWindowPos{}
    , m_iClickedTileIndex(-1)
    , m_iClickedColliderType(0)
    , m_iDrawingType(0)
    , m_iOutputType(0)
    , m_bMouseOver(false)
    , m_TileMapData{}
    , m_bDataSync(true)
    , m_bDataSend(false)
    , m_bCreateBGFlag(false)
    , m_bChangedBGDataFlag(false)
    , m_iBackgroundDataSelector(0)
    , m_bBackgroundSend(false)
{
    m_fTileWindowWidth = (m_fTileSize + m_fSpacing) * 4.7f;
    m_vWindowSize = ImVec2(m_fTileWindowWidth, std::ceil(m_vSRV.size() / 4.0f)* (m_fTileSize + m_fSpacing));
}

MapEditor::~MapEditor()
{
    m_vSRV.clear();
}

void MapEditor::Init(const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV)
{
    m_vSRV = vSRV;
	// 여러 장의 Texture를 로드한다.
}

void MapEditor::Update()
{
    if (ImGui::Begin("Map Editor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        UpdateUIHoverState();

        if (ImGui::IsWindowFocused())
        {
            m_vWindowPos = ImGui::GetWindowPos();
        }
        ImGui::SetWindowSize(m_vWindowSize);

        if (ImGui::BeginTabBar("Tab"))
        {
            UpdateOptionSelection();
            UpdateTileSelection();
            UpdateBGSelection();
            // 배경 추가
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void MapEditor::SetTileMapData(const TileMapData& tileMapData)
{
    m_TileMapData = tileMapData;
}

void MapEditor::ColliderTypeUI_Update()
{
    ImGui::BeginGroup();
    ImGui::Text("Collider Type");
    ImGui::RadioButton("None", &m_iClickedColliderType, 0);
    ImGui::RadioButton("Wall", &m_iClickedColliderType, 1);
    ImGui::RadioButton("Foothold", &m_iClickedColliderType, 2);
    ImGui::EndGroup();
}

void MapEditor::DrawingTypeUI_Update()
{
    ImGui::BeginGroup();
    ImGui::Text("Drawing Mode");
    ImGui::RadioButton("Dragging", &m_iDrawingType, 0);
    ImGui::RadioButton("Pen", &m_iDrawingType, 1);
    ImGui::EndGroup();
}

void MapEditor::TileButtonUI_Update()
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

void MapEditor::OutputTypeUI_Update()
{
    ImGui::BeginGroup();
    ImGui::Text("Output Mode");
    ImGui::RadioButton("Write", &m_iOutputType, 0);
    ImGui::RadioButton("Erase", &m_iOutputType, 1);
    ImGui::EndGroup();
}

void MapEditor::UpdateOptionSelection()
{
    if (ImGui::BeginTabItem("Option"))
    {
        // 저장, 불러오기
        if (ImGui::Button("Save"))
        {
            assert(m_TileMapData.iTileCount != 0);
            ImGuiFileDialog::Instance()->OpenDialog("Save", "Save File", ".map", ".");
        }

        if (ImGuiFileDialog::Instance()->Display("Save"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
                std::wofstream ofs(szPath, std::ios::app | std::ios::out);

                uint32 iCount = m_TileMapData.iTileCount;
                ofs << iCount << L'\n';

                for (uint32 i = 0; i < iCount; ++i)
                {
                    ofs << m_TileMapData.vTileData[i].szTexPath << L'\n';
                    ofs << m_TileMapData.vTileData[i].vTilePos.x << L" " << m_TileMapData.vTileData[i].vTilePos.y << L'\n';
                }
                
                size_t iBGCount = m_vBackgroundDataList.size();
                ofs << iBGCount << L'\n';

                for (uint32 i = 0; i < iBGCount; ++i)
                {
                    ofs << AbsolutePathToRelativePath(m_vBackgroundDataList[i].szBGImagePath) << L'\n';
                    ofs << m_vBackgroundDataList[i].vBGPos.x << L" " << m_vBackgroundDataList[i].vBGPos.y << L" " << m_vBackgroundDataList[i].vBGPos.z << L'\n';
                    ofs << m_vBackgroundDataList[i].vBGScale.x << L" " << m_vBackgroundDataList[i].vBGScale.y << L" " << 1.f << L'\n';
                }
                    
                ofs.close();
            }
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::SameLine();
        
        if (ImGui::Button("Load"))
        {
            
            ImGuiFileDialog::Instance()->OpenDialog("Load", "Load File", ".map", ".");
        }

        if (ImGuiFileDialog::Instance()->Display("Load"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                m_bDataSync = false;

                fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
                std::wifstream ifs(szPath, std::ios::in);

                uint32 iCount = 0;
                ifs >> iCount;

                ifs.ignore(1);

                assert(iCount != 0);
                m_TileMapData.vTileData.resize(iCount);
                m_TileMapData.iTileCount = iCount;

                for (uint32 i = 0; i < iCount; ++i)
                {
                    ifs >> m_TileMapData.vTileData[i].szTexPath;
                    ifs.ignore(1);
                    ifs >> m_TileMapData.vTileData[i].vTilePos.x >> m_TileMapData.vTileData[i].vTilePos.y;
                    ifs.ignore(1);
                }

                uint32 iBGCount = 0;
                ifs >> iBGCount;

                m_vBackgroundDataList.clear();
                m_vBackgroundDataList.resize(iBGCount);

                for (uint32 i = 0; i < iBGCount; ++i)
                {
                    ifs >> m_vBackgroundDataList[i].szBGImagePath;
                    ifs.ignore(1);
                    ifs >> m_vBackgroundDataList[i].vBGPos.x >> m_vBackgroundDataList[i].vBGPos.y >> m_vBackgroundDataList[i].vBGPos.z;
                    ifs.ignore(1);
                    ifs >> m_vBackgroundDataList[i].vBGScale.x >> m_vBackgroundDataList[i].vBGScale.y;
                    ifs.ignore(1);
                }

                ifs.close();
            }
            ImGuiFileDialog::Instance()->Close();
        }

        if (!m_bDataSync)
        {
            m_bDataSend = true;
        }

        InsertSeparator();

        ColliderTypeUI_Update();

        InsertSeparator();

        DrawingTypeUI_Update();

        InsertSeparator();

        OutputTypeUI_Update();

        ImGui::EndTabItem();
    }
}

void MapEditor::UpdateTileSelection()
{
    if (ImGui::BeginTabItem("Tile"))
    {
        TileButtonUI_Update();
        ImGui::EndTabItem();
    }
}

void MapEditor::UpdateUIHoverState()
{
    ImVec2 vPos = ImGui::GetWindowPos();
    ImVec2 vSize = ImGui::GetWindowSize();
    vSize = ImVec2(vPos.x + vSize.x, vPos.y + vSize.y);
    m_bMouseOver = ImGui::IsMouseHoveringRect(vPos, vSize);
}

void MapEditor::UpdateBGSelection()
{
    if (ImGui::BeginTabItem("Background"))
    {
        // 배경 오브젝트를 추가할 수 있고, 배경오브젝트의 스케일, 위치를 설정할 수 있다.

        if (ImGui::Button("Load Image"))
        {
            ImGuiFileDialog::Instance()->OpenDialog("BG_Load", "Load Image", ".png", ".");
        }

        if (ImGuiFileDialog::Instance()->Display("BG_Load"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
                m_szBGImagePath = szPath;

            }
            ImGuiFileDialog::Instance()->Close();
        }
        InsertSeparator();

        ImGui::Text("ImagePath     ");
        ImGui::SameLine();
        ImGui::InputText("ImagePath", const_cast<char*>(ws2s(m_szBGImagePath).c_str()), m_szBGImagePath.size());

        ImGui::Text("Position      ");
        ImGui::SameLine();
        ImGui::InputFloat3("Position", &m_vBGPos.x);

        ImGui::Text("Scale         ");
        ImGui::SameLine();
        ImGui::InputFloat3("Scale", &m_vBGScale.x);

        if (ImGui::Button("Create BG"))
        {
            assert(!m_szBGImagePath.empty());
            // Create Flag On!
            m_bCreateBGFlag = true;

            m_vBackgroundDataList.push_back(BackgroundData{ m_szBGImagePath, m_vBGPos, m_vBGScale });
        }

        InsertSeparator();

        ImGui::Text("Background List:");

        if (ImGui::ListBoxHeader("##itemsBg", ImVec2(-1, 100)))
        {
            for (int i = 0; i < m_vBackgroundDataList.size(); i++)
            {
                string szLabel = "Background_" + std::to_string(i);
                if (ImGui::Selectable(szLabel.c_str(), m_iBackgroundDataSelector == i))
                {
                    m_iBackgroundDataSelector = i;

                    if (!m_vBackgroundDataList.empty())
                    {
                        m_CurrBackgroundData = m_vBackgroundDataList[i];
                    }
                }
            }
            ImGui::ListBoxFooter();
        }

        InsertSeparator();
        ImGui::Text("ImagePath     ");
        ImGui::SameLine();
        ImGui::InputText("EditImagePath", const_cast<char*>(ws2s(m_CurrBackgroundData.szBGImagePath).c_str()), m_CurrBackgroundData.szBGImagePath.size());


        ImGui::Text("Position      ");
        ImGui::SameLine();
        ImGui::InputFloat3("          ", &m_CurrBackgroundData.vBGPos.x);

        ImGui::Text("Scale         ");
        ImGui::SameLine();
        ImGui::InputFloat3("            ", &m_CurrBackgroundData.vBGScale.x);

        if (ImGui::Button("Edit Data"))
        {
            if (!m_vBackgroundDataList.empty())
            {
                m_vBackgroundDataList[m_iBackgroundDataSelector] = m_CurrBackgroundData;
                m_bChangedBGDataFlag = true;
            }
        }

        ImGui::EndTabItem();
    }

}

