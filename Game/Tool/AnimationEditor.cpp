#include "AnimationEditor.h"

AnimationEditor::AnimationEditor()
    :m_bHasAtlasTexture(false)
    , m_vWindowSize(300.f, 800.f)
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

        if (ImGui::Button("Open"))
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.tga,.jpeg,.jpg,.bmp", ".");

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                m_szAtlasTexturePath = s2ws(ImGuiFileDialog::Instance()->GetFilePathName());
                m_szAtlasTextureKey = fs::path(m_szAtlasTexturePath).filename();
            }
            ImGuiFileDialog::Instance()->Close();
        }
    }
    ImGui::End();
}
