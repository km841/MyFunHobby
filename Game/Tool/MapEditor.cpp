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
    , m_iConditionSelector(0)
    , m_iEventSelector(0)
    , m_iEventListSelector(0)
{
    m_fTileWindowWidth = (m_fTileSize + m_fSpacing) * 4.7f;
    m_vWindowSize = ImVec2(m_fTileWindowWidth + 10.f, std::ceil(m_vSRV[static_cast<uint8>(SRV_KIND::TILE)].size() / 4.0f) * (m_fTileSize + m_fSpacing));
}

MapEditor::~MapEditor()
{
    for (int32 i = 0; i < SRV_KIND_COUNT; ++i)
    {
        m_vSRV[i].clear();
    }
}

void MapEditor::Init(const std::array<std::vector<ComPtr<ID3D11ShaderResourceView>>, SRV_KIND_COUNT>& vSRV)
{
    m_vSRV = vSRV;
	// ���� ���� Texture�� �ε��Ѵ�.
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
            UpdateDOSelection();
            UpdateDESelection();
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
    for (int i = 0; i < m_vSRV[static_cast<uint8>(SRV_KIND::TILE)].size(); ++i) {
        ImGui::PushID(i);
        ImGui::ImageButton(m_vSRV[static_cast<uint8>(SRV_KIND::TILE)][i].Get(), ImVec2(m_fTileSize, m_fTileSize));

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

    if (ImGui::IsWindowFocused()) 
    {
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
        // ����, �ҷ�����
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

                size_t iBGCount = m_vBackgroundDataList.size();
                ofs << iBGCount << L'\n';

                for (uint32 i = 0; i < iBGCount; ++i)
                {
                    ofs << AbsolutePathToRelativePath(m_vBackgroundDataList[i].szBGImagePath) << L'\n';
                    ofs << m_vBackgroundDataList[i].vBGPos.x << L" " << m_vBackgroundDataList[i].vBGPos.y << L" " << m_vBackgroundDataList[i].vBGPos.z << L'\n';
                    ofs << m_vBackgroundDataList[i].vBGScale.x << L" " << m_vBackgroundDataList[i].vBGScale.y << L" " << 1.f << L'\n';
                }

                uint32 iCount = m_TileMapData.iTileCount;
                ofs << iCount << L'\n';

                for (uint32 i = 0; i < iCount; ++i)
                {
                    ofs << m_TileMapData.vTileData[i].szTexPath << L'\n';
                    ofs << m_TileMapData.vTileData[i].vTilePos.x << L" " << m_TileMapData.vTileData[i].vTilePos.y << L'\n';
                }
                
                size_t iGateCount = m_TileMapData.vDOData.size();
                ofs << iGateCount << L'\n';

                for (uint32 i = 0; i < iGateCount; ++i)
                {
                    ofs << static_cast<uint8>(m_TileMapData.vDOData[i].eDungeonObjType) << '\n';
                    ofs << static_cast<uint8>(m_TileMapData.vDOData[i].eStageKind) << '\n';
                    ofs << static_cast<uint8>(m_TileMapData.vDOData[i].eDungeonType) << '\n';
                    ofs << m_TileMapData.vDOData[i].szTexPath << L'\n';
                    ofs << m_TileMapData.vDOData[i].vDOPos.x << L" " << m_TileMapData.vDOData[i].vDOPos.y << L'\n';
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
                    ifs >> m_vBackgroundDataList[i].vBGScale.x >> m_vBackgroundDataList[i].vBGScale.y >> m_vBackgroundDataList[i].vBGScale.z;
                    ifs.ignore(1);
                }

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

                uint32 iGateCount = 0;
                ifs >> iGateCount;
                m_TileMapData.vDOData.resize(iGateCount);

                for (uint32 i = 0; i < iGateCount; ++i)
                {
                    uint32 iDungeonObjTypeEnum = 0;
                    ifs >> iDungeonObjTypeEnum;
                    ifs.ignore(1);
                    m_TileMapData.vDOData[i].eDungeonObjType = static_cast<DUNGEON_OBJ_TYPE>(iDungeonObjTypeEnum);

                    uint32 iStageKindEnum = 0;
                    ifs >> iStageKindEnum;
                    ifs.ignore(1);
                    m_TileMapData.vDOData[i].eStageKind = static_cast<STAGE_KIND>(iStageKindEnum);

                    uint32 iDungeonTypeEnum = 0;
                    ifs >> iDungeonTypeEnum;
                    ifs.ignore(1);
                    m_TileMapData.vDOData[i].eDungeonType = static_cast<DUNGEON_TYPE>(iDungeonTypeEnum);

                    ifs >> m_TileMapData.vDOData[i].szTexPath;
                    ifs.ignore(1);
                    ifs >> m_TileMapData.vDOData[i].vDOPos.x >> m_TileMapData.vDOData[i].vDOPos.y;
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
        // ��� ������Ʈ�� �߰��� �� �ְ�, ��������Ʈ�� ������, ��ġ�� ������ �� �ִ�.

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
        ImGui::InputText("                                           ", const_cast<char*>(ws2s(m_CurrBackgroundData.szBGImagePath).c_str()), m_CurrBackgroundData.szBGImagePath.size());


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

void MapEditor::UpdateDOSelection()
{
    if (ImGui::BeginTabItem("DungeonObject"))
    {
        ImGui::Text("DungeonGate");
        int32 iTileGroupSize = static_cast<int32>(m_vSRV[static_cast<uint8>(SRV_KIND::TILE)].size());
        int32 iDungeonGateGroupSize = static_cast<int32>(m_vSRV[static_cast<uint8>(SRV_KIND::DUNGEON_GATE)].size());
        int32 iDungeonWallGroupSize = static_cast<int32>(m_vSRV[static_cast<uint8>(SRV_KIND::DUNGEON_WALL)].size());

        // ���� ����Ʈ�� �÷��̾�� ��ȣ�ۿ��ϴ� ������Ʈ��, �� Ŭ���� �� ���� ��ħ�� ���� �߰��� �� �ִ�.
        for (int32 i = 0; i < iDungeonGateGroupSize; ++i) {
            ImGui::PushID(i + iTileGroupSize);
            ImGui::ImageButton(m_vSRV[static_cast<uint8>(SRV_KIND::DUNGEON_GATE)][i].Get(), ImVec2(m_fTileSize, m_fTileSize));

            if (ImGui::IsItemClicked())
            {
                m_iClickedTileIndex = i + iTileGroupSize;
            }

            ImGui::PopID();
            if ((i + 1) % 4 != 0)
            {
                ImGui::SameLine(0.0f, m_fSpacing);
            }
        }

        InsertSeparator();
        ImGui::Text("DungeonWall");
        
        for (int32 i = 0; i < iDungeonWallGroupSize; ++i) {
            ImGui::PushID(i + iTileGroupSize + iDungeonGateGroupSize);
            ImGui::ImageButton(m_vSRV[static_cast<uint8>(SRV_KIND::DUNGEON_WALL)][i].Get(), ImVec2(m_fTileSize, m_fTileSize));

            if (ImGui::IsItemClicked())
            {
                m_iClickedTileIndex = i + iTileGroupSize + iDungeonGateGroupSize;
            }

            ImGui::PopID();
            if ((i + 1) % 4 != 0)
            {
                ImGui::SameLine(0.0f, m_fSpacing);
            }
        }

        if (ImGui::IsWindowFocused())
        {
            ImVec2 vDelta = ImVec2(ImGui::GetWindowPos().x - m_vWindowPos.x, ImGui::GetWindowPos().y - m_vWindowPos.y);
            for (int i = 0; i < m_vSRV.size(); ++i) {
                ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + vDelta.x, ImGui::GetCursorPos().y + vDelta.y));
            }
        }
       
        ImGui::EndTabItem();
    }
}

void MapEditor::UpdateDESelection()
{
    if (ImGui::BeginTabItem("DungeonEvent"))
    {
        if (ImGui::Button("Event Save"))
        {
            assert(m_vEventList.size() > 0);
            ImGuiFileDialog::Instance()->OpenDialog("Event Save", "Save Event File", ".evtscript", ".");
        }

        if (ImGuiFileDialog::Instance()->Display("Event Save"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
                std::wofstream ofs(szPath, std::ios::app | std::ios::out);

                size_t iEventCount = m_vEventList.size();
                ofs << iEventCount << L'\n';

                for (uint32 i = 0; i < iEventCount; ++i)
                {
                    ofs << static_cast<int32>(m_vEventList[i].eEventKind) << L'\n';
                    ofs << static_cast<int32>(m_vEventList[i].eCondition) << L'\n';
                    ofs << m_vEventList[i].eEnum1 << L'\n';
                    ofs << m_vEventList[i].eEnum2 << L'\n';
                    ofs << m_vEventList[i].vVec3.x << L' ' << m_vEventList[i].vVec3.y << L' ' << m_vEventList[i].vVec3.z << '\n';
                }

                ofs.close();

            }
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::SameLine();

        if (ImGui::Button("Event Load"))
        {
            ImGuiFileDialog::Instance()->OpenDialog("Event Load", "Load Event File", ".evtscript", ".");
        }

        if (ImGuiFileDialog::Instance()->Display("Event Load"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
                std::wifstream ifs(szPath, std::ios::in);

                uint32 iEventCount = 0;
                ifs >> iEventCount;

                m_vEventList.clear();
                m_vEventList.resize(iEventCount);

                for (uint32 i = 0; i < iEventCount; ++i)
                {
                    int32 iEventKind = 0;
                    ifs >> iEventKind;
                    m_vEventList[i].eEventKind = static_cast<DUNGEON_EVENT_KIND>(iEventKind);
                    ifs.ignore(1);

                    int32 iCondition = 0;
                    ifs >> iCondition;
                    m_vEventList[i].eCondition = static_cast<CONDITION_TYPE>(iCondition);
                    ifs.ignore(1);

                    ifs >> m_vEventList[i].eEnum1;
                    ifs.ignore(1);
                    ifs >> m_vEventList[i].eEnum2;
                    ifs.ignore(1);

                    ifs >> m_vEventList[i].vVec3.x >> m_vEventList[i].vVec3.y >> m_vEventList[i].vVec3.z;
                    ifs.ignore(1);
                }

                ifs.close();
            }
            ImGuiFileDialog::Instance()->Close();
        }

        std::vector<string> vConditionNames = {};
        for (int32 i = 0; i < CONDITION_TYPE_COUNT; ++i)
        {
            vConditionNames.push_back(ConditionEnumToString(static_cast<CONDITION_TYPE>(i)));
        }

        std::vector<string> vEventNames = {};
        for (int32 i = 0; i < DUNGEON_EVENT_COUNT; ++i)
        {
            vEventNames.push_back(EventEnumToString(static_cast<DUNGEON_EVENT_KIND>(i)));
        }


        if (ImGui::BeginCombo("Condition", vConditionNames[m_iConditionSelector].c_str()))
        {
            for (int32 i = 0; i < vConditionNames.size(); i++)
            {
                const bool isSelected = (m_iConditionSelector == i);
                if (ImGui::Selectable(vConditionNames[i].c_str(), isSelected))
                {
                    m_iConditionSelector = i;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("Event", vEventNames[m_iEventSelector].c_str()))
        {
            for (int32 i = 0; i < vEventNames.size(); i++)
            {
                const bool isSelected = (m_iEventSelector == i);
                if (ImGui::Selectable(vEventNames[i].c_str(), isSelected))
                {
                    m_iEventSelector = i;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        DUNGEON_EVENT_KIND eEventSelect = static_cast<DUNGEON_EVENT_KIND>(m_iEventSelector);
        switch (eEventSelect)
        {
        case DUNGEON_EVENT_KIND::MONSTER_SPAWN:
            MonsterSpawnEventUIUpdate();
            break;

        case DUNGEON_EVENT_KIND::CREATE_TREASURE:
            break;

        case DUNGEON_EVENT_KIND::PLAYER_TELEPORT:
            PlayerTeleportEventUIUpdate();
            break;
        }

        ImGui::Text("Event List:");

        if (ImGui::ListBoxHeader("##itemsEvent", ImVec2(-1, 100)))
        {
            for (int i = 0; i < m_vEventList.size(); i++)
            {
                string szLabel = "Event_" + std::to_string(i);
                if (ImGui::Selectable(szLabel.c_str(), m_iEventListSelector == i))
                {
                    m_iEventListSelector = i;

                    if (!m_vEventList.empty())
                    {
                        m_CurrEventInfo = m_vEventList[i];
                    }
                }
            }
            ImGui::ListBoxFooter();
        }

        InsertSeparator();

        string szEventName = EventEnumToString(m_CurrEventInfo.eEventKind);
        string szConditionName = ConditionEnumToString(m_CurrEventInfo.eCondition);

        ImGui::Text("ConditionName");
        ImGui::SameLine();
        ImGui::InputText("                                 ", const_cast<char*>(szConditionName.c_str()), szConditionName.size());

        ImGui::Text("EventName    ");
        ImGui::SameLine();
        ImGui::InputText("                               ", const_cast<char*>(szEventName.c_str()), szEventName.size());

        ImGui::Text("Enum1        ");
        ImGui::SameLine();
        ImGui::InputInt("                         ", &m_CurrEventInfo.eEnum1);

        ImGui::Text("Enum2        ");
        ImGui::SameLine();  
        ImGui::InputInt("                    ", &m_CurrEventInfo.eEnum2);

        ImGui::Text("Vec3_1       ");
        ImGui::SameLine();
        ImGui::InputFloat3("                    ", &m_CurrEventInfo.vVec3.x);

        if (ImGui::Button("Add Event"))
        {
            m_InputEventInfo.eCondition = static_cast<CONDITION_TYPE>(m_iConditionSelector);
            m_InputEventInfo.eEventKind = static_cast<DUNGEON_EVENT_KIND>(m_iEventSelector);
            m_vEventList.push_back(m_InputEventInfo);
        }

        ImGui::EndTabItem();
    }
}

string MapEditor::ConditionEnumToString(CONDITION_TYPE eConditionType)
{
    switch (eConditionType)
    {
    case CONDITION_TYPE::ALWAYS_TRUE:
        return "Always True";
    case CONDITION_TYPE::ALL_MONSTER_DEAD_IN_DUNGEON:
        return "All Monster Dead In Dungeon";
    }

    return "Not Found";
}

string MapEditor::EventEnumToString(DUNGEON_EVENT_KIND eEventKind)
{
    switch (eEventKind)
    {
    case DUNGEON_EVENT_KIND::MONSTER_SPAWN:
        return "Monster Spawn";
    case DUNGEON_EVENT_KIND::CREATE_TREASURE:
        return "Create Treasure";
    case DUNGEON_EVENT_KIND::PLAYER_TELEPORT:
        return "Player Teleport";
    }

    return "Not Found";
}

void MapEditor::MonsterSpawnEventUIUpdate()
{
    InsertSeparator();
    ImGui::Text("MonsterSpawn Event Parameters");

    std::vector<string> vMonsterKind = {};
    for (int32 i = 0; i < MONSTER_KIND_COUNT; ++i)
    {
        vMonsterKind.push_back(MonsterKindEnumToString(static_cast<MONSTER_KIND>(i)));
    }

    static int32 iMonsterSelector = 0;
    if (ImGui::BeginCombo("MonsterKind", vMonsterKind[iMonsterSelector].c_str()))
    {
        for (int32 i = 0; i < vMonsterKind.size(); i++)
        {
            const bool isSelected = (iMonsterSelector == i);
            if (ImGui::Selectable(vMonsterKind[i].c_str(), isSelected))
            {
                iMonsterSelector = i;
            }
            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    m_InputEventInfo.eEnum1 = iMonsterSelector;
    ImGui::InputFloat3("MonsterPosition", &m_InputEventInfo.vVec3.x);
    InsertSeparator();
}

void MapEditor::PlayerTeleportEventUIUpdate()
{
    InsertSeparator();
    ImGui::Text("PlayerTeleport Event Parameters");
    ImGui::InputFloat3("PlayerDescPosition", &m_InputEventInfo.vVec3.x);
    InsertSeparator();
}

string MapEditor::MonsterKindEnumToString(MONSTER_KIND eMonsterKind)
{
    switch (eMonsterKind)
    {
    case MONSTER_KIND::JUNIOR_KNIGHT:
        return "JuniorKnight";
    }

    return "Not Found";
}

