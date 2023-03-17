#include "AnimationEditor.h"

AnimationEditor::AnimationEditor()
    :m_bHasAtlasTexture(false)
    , m_vWindowSize(300.f, 500.f)
    , m_fDuration(0.f)
    , m_fOffset(0.f)
    , m_iFrameSelector(-1)
    , m_bReadable(false)
    , m_CurrFrameData{}
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

        ImGui::SameLine();

        if (ImGui::Button("Set"))
        {
            FlipReadableFlag();
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

        InsertSeparator();

        ImGui::Text("Animation Frames:");

        if (ImGui::ListBoxHeader("##items", ImVec2(-1, 100)))
        {
            for (int i = 0; i < m_vFrameDataList.size(); i++)
            {
                string szLabel = "Animation Frame_" + std::to_string(i);
                if (ImGui::Selectable(szLabel.c_str(), m_iFrameSelector == i))
                {
                    m_iFrameSelector = i;

                    if (!m_vFrameDataList.empty())
                    {
                        m_CurrFrameData = m_vFrameDataList[i];
                    }
                }
            }
            ImGui::ListBoxFooter();
        }

        InsertSeparator();

        ImGui::Text("Frame LT Pos  ");
        ImGui::SameLine();
        ImGui::InputFloat2("     ", &m_CurrFrameData.vLTPos.x);

        ImGui::Text("Frame Size    ");
        ImGui::SameLine();
        ImGui::InputFloat2("       ", &m_CurrFrameData.vSize.x);

        ImGui::Text("Frame Duration");
        ImGui::SameLine();
        ImGui::InputFloat("          ", &m_CurrFrameData.fDuration);

        ImGui::Text("Frame Offset  ");
        ImGui::SameLine();
        ImGui::InputFloat("            ", &m_CurrFrameData.fOffset);

    }
    ImGui::End();
}

void AnimationEditor::InsertFrameData(const FrameData& frameData)
{
    m_vFrameDataList.push_back(frameData);
}

