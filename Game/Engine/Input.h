#pragma once
enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',
	N = 'N',
	G = 'G',
	X = 'X',

	ENTER = VK_RETURN,
	SPACE = VK_SPACE,
	TAB = VK_TAB,

	LBUTTON = MK_LBUTTON,
	RBUTTON = MK_RBUTTON,
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END),
};


class Input
{
	DECLARE_SINGLE(Input);

public:
	void Init(HWND hHwnd);
	void Update();

	bool GetButtonPress(KEY_TYPE eKey)     const { return KEY_STATE::PRESS == GetState(eKey); }
	bool GetButtonDown(KEY_TYPE eKey)      const { return KEY_STATE::DOWN == GetState(eKey); }
	bool GetButtonUp(KEY_TYPE eKey)        const { return KEY_STATE::UP == GetState(eKey); }
	bool GetButtonNone(KEY_TYPE eKey)      const { return KEY_STATE::NONE == GetState(eKey); }
	FORCEINLINE const POINT& GetMousePos() const { return m_MousePos; }

private:
	FORCEINLINE KEY_STATE GetState(KEY_TYPE eKeyType) const { return m_vStates[static_cast<uint8>(eKeyType)]; }

	

private:
	HWND				   m_hHwnd;
	std::vector<KEY_STATE> m_vStates;
	POINT				   m_MousePos;
};

