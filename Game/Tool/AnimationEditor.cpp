#include "AnimationEditor.h"

AnimationEditor::AnimationEditor()
    :m_bHasAtlasTexture(false)
    , m_vWindowSize(300.f, 800.f)
    , m_fDuration(0.f)
    , m_fOffset(0.f)
{

}

AnimationEditor::~AnimationEditor()
{
}

void AnimationEditor::Init()
{
}

void AnimationEditor::Update()
{
    if (ImGui::Begin("Animation Editor", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        ImGui::SetWindowSize(m_vWindowSize);

        // Dialog
        if (ImGui::Button("New"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.tga,.jpeg,.jpg,.bmp", ".");

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                m_szSpriteTexturePath = s2ws(ImGuiFileDialog::Instance()->GetFilePathName());
                m_szSpriteTextureKey = fs::path(m_szSpriteTexturePath).filename();
            }
            ImGuiFileDialog::Instance()->Close();
        }

        // Frame
        InsertSeparator();

        ImGui::Text("LT Pos  ");
        ImGui::SameLine();
        ImGui::InputFloat2("", &m_vLTPos.x);

        ImGui::Text("Size    ");
        ImGui::SameLine();
        ImGui::InputFloat2("  ", &m_vSize.x);

        ImGui::Text("Duration");
        ImGui::SameLine();
        ImGui::InputFloat(" ", &m_fDuration);

        ImGui::Text("Offset  ");
        ImGui::SameLine();
        ImGui::InputFloat("   ", &m_fOffset);
    }
    ImGui::End();
}
