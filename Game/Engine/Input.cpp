#include "pch.h"
#include "Input.h"
#include "Engine.h"

void Input::Init(HWND hHwnd)
{
	m_hHwnd = hHwnd;
	m_vStates.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
	// 리사이즈로 초기화할 수도 있구나!
}

void Input::Update()
{
	HWND hHwnd = GetActiveWindow();

	if (m_hHwnd != hHwnd)
	{
		for (uint32 i = 0; i < KEY_TYPE_COUNT; ++i)
			m_vStates[i] = KEY_STATE::NONE;

		return;
	}

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (false == GetKeyboardState(asciiKeys))
		return;

	for (uint32 i = 0; i < KEY_TYPE_COUNT; ++i)
	{
		if (asciiKeys[i] & 0x80)
		{
			KEY_STATE& eState = m_vStates[i];
			
			if (KEY_STATE::PRESS == eState || KEY_STATE::DOWN == eState)
				eState = KEY_STATE::PRESS;
			else
				eState = KEY_STATE::DOWN;
		}

		else
		{
			KEY_STATE& eState = m_vStates[i];

			if (KEY_STATE::PRESS == eState || KEY_STATE::DOWN == eState)
				eState = KEY_STATE::UP;
			else
				eState = KEY_STATE::NONE;
		}
	}

	::GetCursorPos(&m_MousePos);
	::ScreenToClient(g_pEngine->GetHwnd(), &m_MousePos);
}
