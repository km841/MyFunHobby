#include "AnimationEditor.h"

AnimationEditor::AnimationEditor()
    :m_bHasAtlasTexture(false)
    , m_fDuration(0.f)
    , m_iFrameSelector(-1)
    , m_bReadable(false)
    , m_CurrFrameData{}
    , m_bLoop(false)
    , m_bPlaying(false)
    , m_szName{}
{
    m_vWindowSize = ImVec2(350.f, 530.f);
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
                m_szSpriteTextureKeyStr = ws2s(m_szSpriteTextureKey);
            }
            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::SameLine();

        if (ImGui::Button("Set"))
        {
            FlipReadableFlag();
        }
        ImGui::SameLine();
        if (ImGui::Button("Edit"))
        {
            FlipReadableFlag();
        }

        // Frame
        InsertSeparator();

        ImGui::Text("Name          ");
        ImGui::SameLine();
        ImGui::InputText("                    ", m_szName, sizeof(m_szName));

        ImGui::Text("LT Pos        ");
        ImGui::SameLine();
        ImGui::InputFloat2("", &m_vLTPos.x);

        ImGui::Text("Size          ");
        ImGui::SameLine();
        ImGui::InputFloat2("  ", &m_vSize.x);

        ImGui::Text("Duration      ");
        ImGui::SameLine();
        ImGui::InputFloat(" ", &m_fDuration);

        ImGui::Text("Offset        ");
        ImGui::SameLine();
        ImGui::InputFloat2("   ", &m_vOffset.x);

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

        ImGui::Text("Animation Name");
        ImGui::SameLine();
        ImGui::InputText("     ", const_cast<char*>(ws2s(m_CurrFrameData.szName).c_str()), m_CurrFrameData.szName.size());

        ImGui::Text("Tex Path      ");
        ImGui::SameLine();
        ImGui::InputText("     ", const_cast<char*>(ws2s(m_CurrFrameData.szTexPath).c_str()), m_CurrFrameData.szTexPath.size());

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
        ImGui::InputFloat2("            ", &m_CurrFrameData.vOffset.x);

        if (ImGui::Button("Edit Data"))
        {
            if (!m_vFrameDataList.empty())
            {
                m_vFrameDataList[m_iFrameSelector] = m_CurrFrameData;
            }
        }

        InsertSeparator();

        ImGui::Text("Animation Test");
        ImGui::SameLine();
        if (ImGui::Button("Play"))
        {
            m_bPlaying = true;

        }
        ImGui::SameLine();
        if (ImGui::Button("Stop"))
        {
            m_bPlaying = false;
        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Checkbox("Loop", &m_bLoop);

    }
    ImGui::End();
}

void AnimationEditor::InsertFrameData(const FrameData& frameData)
{
    m_vFrameDataList.push_back(frameData);
}

