#include "AnimationEditor.h"

AnimationEditor::AnimationEditor()
    :m_bHasAtlasTexture(false)
    , m_fDuration(0.f)
    , m_iFrameSelector(-1)
    , m_bReadable(false)
    , m_CurrFrameData{}
    , m_bLoop(false)
    , m_bPlaying(false)
    , m_bSpriteUpdate(false)
    , m_szName{}
    , m_bAllChange(false)
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

        NewButtonUI_Update();
          ImGui::SameLine();

        OpenButtonUI_Update();
          ImGui::SameLine();

        SaveButtonUI_Update();
          ImGui::SameLine();

        SetButtonUI_Update();
          InsertSeparator();

        InputUI_Update();
          InsertSeparator();

        FrameListUI_Update();
          InsertSeparator();
        
        EditUI_Update();
          InsertSeparator();

        AnimUI_Update();
    }
    ImGui::End();
}

void AnimationEditor::InsertFrameData(const FrameData& frameData)
{
    m_vFrameDataList.push_back(frameData);
}

void AnimationEditor::NewButtonUI_Update()
{
    if (ImGui::Button("New"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png,.tga", ".");

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            m_szSpriteTexturePath = s2ws(ImGuiFileDialog::Instance()->GetFilePathName());
            if (!m_szSpriteTexturePath.empty())
                m_bSpriteUpdate = true;
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void AnimationEditor::OpenButtonUI_Update()
{
    if (ImGui::Button("Open"))
        ImGuiFileDialog::Instance()->OpenDialog("Open", "Open File", ".anim", ".");

    if (ImGuiFileDialog::Instance()->Display("Open"))
    {
        m_vFrameDataList.clear();

        if (ImGuiFileDialog::Instance()->IsOk())
        {
            fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
            std::wifstream ifs(szPath, std::ios::in);

            int32 iCount = 0;
            wstring szTexPath, szName;

            ifs >> iCount;
            ifs.ignore(1);

            assert(iCount != 0);

            getline(ifs, szName);
            getline(ifs, szTexPath);

            szPath = szTexPath;

            m_vFrameDataList.resize(iCount);

            for (int32 i = 0; i < iCount; ++i)
            {
                ifs >> m_vFrameDataList[i].vLTPos.x >> m_vFrameDataList[i].vLTPos.y;
                ifs.ignore(1);
                ifs >> m_vFrameDataList[i].vSize.x >> m_vFrameDataList[i].vSize.y;
                ifs.ignore(1);
                ifs >> m_vFrameDataList[i].vOffset.x >> m_vFrameDataList[i].vOffset.y;
                ifs.ignore(1);
                ifs >> m_vFrameDataList[i].fDuration;
                ifs.ignore(1);

                m_vFrameDataList[i].szName = szName;
                m_vFrameDataList[i].szTexPath = szTexPath;
                m_vFrameDataList[i].iFrameCount = iCount;

                m_szSpriteTexturePath = szPath;
            }

            ifs.close();
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void AnimationEditor::SaveButtonUI_Update()
{
    if (ImGui::Button("Save"))
        ImGuiFileDialog::Instance()->OpenDialog("Save", "Save File", ".anim", ".");

    if (ImGuiFileDialog::Instance()->Display("Save"))
    {
        assert(!m_vFrameDataList.empty());

        if (ImGuiFileDialog::Instance()->IsOk())
        {
            fs::path szPath = ImGuiFileDialog::Instance()->GetFilePathName();
            std::wofstream ofs(szPath, std::ios::app | std::ios::out);

            int32 iCount = m_vFrameDataList[0].iFrameCount;
            wstring szTexPath = m_vFrameDataList[0].szTexPath;
            wstring szName = m_vFrameDataList[0].szName;
            ofs << iCount << L'\n';
            ofs << szName << L'\n';
            ofs << szTexPath << L'\n';

            for (int32 i = 0; i < iCount; ++i)
            {
                ofs << m_vFrameDataList[i].vLTPos.x << L" " << m_vFrameDataList[i].vLTPos.y << '\n';
                ofs << m_vFrameDataList[i].vSize.x << L" " << m_vFrameDataList[i].vSize.y << '\n';
                ofs << m_vFrameDataList[i].vOffset.x << L" " << m_vFrameDataList[i].vOffset.y << '\n';
                ofs << m_vFrameDataList[i].fDuration << L'\n';
            }

            ofs.close();
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

void AnimationEditor::SetButtonUI_Update()
{
    ImGui::Spacing();
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    if (ImGui::Button("Set"))
    {
        FlipReadableFlag();
    }
}

void AnimationEditor::InputUI_Update()
{
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
}

void AnimationEditor::EditUI_Update()
{
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

    ImGui::Text("Duration All Change");
    ImGui::SameLine();
    ImGui::Checkbox("                       ", &m_bAllChange);

    if (ImGui::Button("Edit Data"))
    {
        if (!m_vFrameDataList.empty())
        {
            m_vFrameDataList[m_iFrameSelector] = m_CurrFrameData;

            if (m_bAllChange)
            {
                for (auto& frameData : m_vFrameDataList)
                    frameData.fDuration = m_CurrFrameData.fDuration;
            }

        }
    }
}

void AnimationEditor::FrameListUI_Update()
{
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
}

void AnimationEditor::AnimUI_Update()
{
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

