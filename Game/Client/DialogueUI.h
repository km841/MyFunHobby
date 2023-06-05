#pragma once
#include "UI.h"
class DialogueUI :
    public UI
{
public:
    DialogueUI();
    virtual ~DialogueUI();

public:
    virtual void Awake();
    virtual void Start();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Action();

    void SetTalkerAndLine(const wstring& szTalker, const wstring& szLine, float fDuration);

private:
    wstring m_szTalker;
    wstring m_szLine;
    bool m_bStartFlag;
    int32 m_iContext;
    Timer m_tDuration;

    const Vec3 m_vTalkerFontPos = Vec3(625.f, 192.f, 0.f);
    const Vec3 m_vLineFontPos = Vec3(500.f, 145.f, 0.f);
    const Color m_TalkerFontColor = Color::FromRGB(211, 198, 192);
    const Color m_LineFontColor = Color::FromRGB(174, 156, 122);
    const float m_fTalkerFontSize = 23.f;
    const float m_fLineFontSize = 20.f;
};

