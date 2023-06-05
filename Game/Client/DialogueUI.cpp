#include "pch.h"
#include "DialogueUI.h"
#include "Engine.h"
#include "Clock.h"

DialogueUI::DialogueUI()
	: m_bStartFlag(false)
	, m_iContext(0)
	, m_tDuration(0.f)
{
}

DialogueUI::~DialogueUI()
{
}

void DialogueUI::Awake()
{
	UI::Awake();
}

void DialogueUI::Start()
{
	UI::Start();
}

void DialogueUI::Update()
{
	UI::Update();

	if (IsDisable())
		return;

	if (m_bStartFlag)
	{
		FONT->DrawString(m_szTalker, m_fTalkerFontSize, m_vTalkerFontPos, FONT_WEIGHT::ULTRA_BOLD, m_TalkerFontColor, FONT_ALIGN::CENTER);

		if (m_iContext >= m_szLine.size())
		{
			FONT->DrawString(m_szLine.substr(0), m_fLineFontSize, m_vLineFontPos, FONT_WEIGHT::BOLD, m_LineFontColor, FONT_ALIGN::LEFT);
		}
		else
		{
			if (!m_tDuration.IsRunning())
				m_tDuration.Start();

			m_tDuration.Update(WORLD_DELTA_TIME);
			if (m_tDuration.IsFinished())
			{
				m_iContext++;
				m_tDuration.Reset();
			}

			if (m_szLine[m_iContext] == L' ')
				m_iContext++;
				

			FONT->DrawString(m_szLine.substr(0, m_iContext), m_fLineFontSize, m_vLineFontPos, FONT_WEIGHT::BOLD, m_LineFontColor, FONT_ALIGN::LEFT);
		}
	}
}

void DialogueUI::LateUpdate()
{
	UI::LateUpdate();
}

void DialogueUI::FinalUpdate()
{
	UI::FinalUpdate();
}

void DialogueUI::Action()
{
	assert(!m_szTalker.empty());
	assert(!m_szLine.empty());
	m_bStartFlag = true;
	m_iContext = 0;
}

void DialogueUI::SetTalkerAndLine(const wstring& szTalker, const wstring& szLine, float fDuration)
{
	m_szTalker = szTalker;
	m_szLine = szLine;
	m_tDuration.SetEndTime(fDuration / static_cast<float>(m_szLine.size()));
}
