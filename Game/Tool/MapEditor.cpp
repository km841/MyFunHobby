#include "MapEditor.h"

MapEditor::MapEditor()
{
    m_vWindowSize = ImVec2(300.f, 300.f);
}

MapEditor::~MapEditor()
{
}

void MapEditor::Init()
{

}

void MapEditor::Update()
{
    if (ImGui::Begin("Map Editor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        ImGui::SetWindowSize(m_vWindowSize);
    }
    ImGui::End();
}
